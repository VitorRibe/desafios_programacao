#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

const int MAXN = 100005;
const int LOGN = 18;

vector<int> adj[MAXN];
int fav[MAXN], gender[MAXN];
int euler[2 * MAXN], in_time[MAXN], out_time[MAXN], depth[MAXN];
int up[MAXN][LOGN];
int timer = 0;

void dfs(int u, int p, int d) {
    depth[u] = d;
    up[u][0] = p;
    for (int i = 1; i < LOGN; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    euler[++timer] = u;
    in_time[u] = timer;

    for (int v : adj[u]) {
        if (v != p) dfs(v, u, d + 1);
    }

    euler[++timer] = u;
    out_time[u] = timer;
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOGN - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) u = up[u][i];
    }
    if (u == v) return u;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

struct Query {
    int l, r, lca, id, block;
    bool operator<(const Query& other) const {
        if (block != other.block) return block < other.block;
        return (block & 1) ? (r < other.r) : (r > other.r);
    }
};

bool vis[MAXN];
long long cnt_boys[MAXN], cnt_girls[MAXN];
long long pairs_cnt = 0;

inline void toggle(int node) {
    int f = fav[node];
    int g = gender[node];
    if (vis[node]) {
        if (g == 0) {
            pairs_cnt -= cnt_girls[f];
            cnt_boys[f]--;
        } else {
            pairs_cnt -= cnt_boys[f];
            cnt_girls[f]--;
        }
    } else {
        if (g == 0) {
            pairs_cnt += cnt_girls[f];
            cnt_boys[f]++;
        } else {
            pairs_cnt += cnt_boys[f];
            cnt_girls[f]++;
        }
    }
    vis[node] = !vis[node];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Leitura da linha de géneros (1 para rapariga, 0 para rapaz)
    for (int i = 1; i <= n; i++) {
        cin >> gender[i];
    }

    // Leitura da linha de números favoritos com compressão de coordenadas
    map<int, int> compress;
    int comp_id = 1;

    for (int i = 1; i <= n; i++) {
        int f;
        cin >> f;
        if (!compress.count(f)) compress[f] = comp_id++;
        fav[i] = compress[f];
    }

    // Leitura das arestas da árvore
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 1, 0);

    int q;
    cin >> q;
    int block_size = max(1, (int)sqrt(2 * n));
    vector<Query> queries(q);

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        if (in_time[u] > in_time[v]) swap(u, v);
        int lca = get_lca(u, v);

        queries[i].id = i;
        if (lca == u) {
            queries[i].l = in_time[u];
            queries[i].r = in_time[v];
            queries[i].lca = 0;
        } else {
            queries[i].l = out_time[u];
            queries[i].r = in_time[v];
            queries[i].lca = lca;
        }
        queries[i].block = queries[i].l / block_size;
    }

    sort(queries.begin(), queries.end());

    vector<long long> ans(q);
    int cur_l = 1, cur_r = 0;

    for (const auto& q_item : queries) {
        while (cur_l > q_item.l) toggle(euler[--cur_l]);
        while (cur_r < q_item.r) toggle(euler[++cur_r]);
        while (cur_l < q_item.l) toggle(euler[cur_l++]);
        while (cur_r > q_item.r) toggle(euler[cur_r--]);

        if (q_item.lca) toggle(q_item.lca);
        ans[q_item.id] = pairs_cnt;
        if (q_item.lca) toggle(q_item.lca);
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
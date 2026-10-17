#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

const int MAXN = 40005;
const int LOGN = 17;

vector<int> adj[MAXN];
int val[MAXN], euler[2 * MAXN], in_time[MAXN], out_time[MAXN], depth[MAXN];
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
int cnt[MAXN];
int distinct_cnt = 0;

inline void toggle(int node) {
    if (vis[node]) {
        cnt[val[node]]--;
        if (cnt[val[node]] == 0) distinct_cnt--;
    } else {
        if (cnt[val[node]] == 0) distinct_cnt++;
        cnt[val[node]]++;
    }
    vis[node] = !vis[node];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    map<int, int> compress;
    int comp_id = 1;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (!compress.count(x)) compress[x] = comp_id++;
        val[i] = compress[x];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 1, 0);

    int block_size = max(1, (int)sqrt(2 * n));
    vector<Query> queries(m);

    for (int i = 0; i < m; i++) {
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

    vector<int> ans(m);
    int cur_l = 1, cur_r = 0;

    for (const auto& q : queries) {
        while (cur_l > q.l) toggle(euler[--cur_l]);
        while (cur_r < q.r) toggle(euler[++cur_r]);
        while (cur_l < q.l) toggle(euler[cur_l++]);
        while (cur_r > q.r) toggle(euler[cur_r--]);

        if (q.lca) toggle(q.lca);
        ans[q.id] = distinct_cnt;
        if (q.lca) toggle(q.lca);
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
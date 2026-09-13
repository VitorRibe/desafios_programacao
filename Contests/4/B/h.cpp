/*
H - Conectividade Dinâmica (Dynamic Connectivity)

Dado um grafo com n nós e m arestas, reporte o número de componentes após cada evento de adicionar ou remover uma aresta.

Entrada:
n, m, k (nós, arestas iniciais, eventos).
m linhas com as arestas.
k linhas "t a b" (1 para criar, 2 para remover).

Saída:
k+1 inteiros: componentes iniciais e após cada evento.
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> sz;
    int comps;
    vector<pair<int, int>> history;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        comps = n;
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return find(parent[i]); 
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
            comps--;
            history.push_back({root_j, root_i}); 
            return true;
        }
        return false;
    }

    void rollback(int checkpoints) {
        while (history.size() > checkpoints) {
            auto op = history.back();
            history.pop_back();
            int child = op.first;
            int p = op.second;
            sz[p] -= sz[child];
            parent[child] = child;
            comps++;
        }
    }
};

map<pair<int, int>, int> active_edges;
vector<pair<int, int>> edges;
vector<pair<int, int>> timeline[400005];
int ans[100005];

void add_edge_to_tree(int node, int l, int r, int ql, int qr, const pair<int, int>& edge) {
    if (ql <= l && r <= qr) {
        timeline[node].push_back(edge);
        return;
    }
    int mid = l + (r - l) / 2;
    if (ql <= mid) add_edge_to_tree(2 * node, l, mid, ql, qr, edge);
    if (qr > mid) add_edge_to_tree(2 * node + 1, mid + 1, r, ql, qr, edge);
}

void solve(int node, int l, int r, DSU& dsu) {
    int checkpoints = dsu.history.size();
    for (size_t i = 0; i < timeline[node].size(); i++) {
        dsu.unite(timeline[node][i].first, timeline[node][i].second);
    }
    
    if (l == r) {
        ans[l] = dsu.comps;
    } else {
        int mid = l + (r - l) / 2;
        solve(2 * node, l, mid, dsu);
        solve(2 * node + 1, mid + 1, r, dsu);
    }
    
    dsu.rollback(checkpoints);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        active_edges[{u, v}] = 0;
    }

    for (int i = 1; i <= k; i++) {
        int type, u, v;
        cin >> type >> u >> v;
        if (u > v) swap(u, v);
        
        if (type == 1) {
            active_edges[{u, v}] = i;
        } else {
            add_edge_to_tree(1, 0, k, active_edges[{u, v}], i - 1, {u, v});
            active_edges.erase({u, v});
        }
    }

    for (auto const& item : active_edges) {
        pair<int, int> edge = item.first;
        int start_time = item.second;
        add_edge_to_tree(1, 0, k, start_time, k, edge);
    }

    DSU dsu(n);
    solve(1, 0, k, dsu);

    for (int i = 0; i <= k; i++) {
        cout << ans[i] << (i == k ? "" : " ");
    }
    cout << "\n";

    return 0;
}
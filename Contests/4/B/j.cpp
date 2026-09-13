/*
J - Consultas de Caminho (Path Queries)

Você recebe uma árvore ponderada de n vértices. Calcule o número de pares (u, v) onde o peso máximo no caminho não excede q_i.

Entrada:
n, m.
n-1 arestas u, v, w.
q_1, ..., q_m.

Saída:
m respostas.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct Query {
    int q, id;
    bool operator<(const Query& other) const {
        return q < other.q;
    }
};

struct DSU {
    vector<int> parent;
    vector<long long> sz;
    long long current_pairs;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        current_pairs = 0;
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
            current_pairs += sz[root_i] * sz[root_j];
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    vector<Query> queries(m);
    for (int i = 0; i < m; i++) {
        cin >> queries[i].q;
        queries[i].id = i;
    }

    sort(edges.begin(), edges.end());
    sort(queries.begin(), queries.end());

    DSU dsu(n);
    vector<long long> ans(m);
    int edge_idx = 0;

    for (int i = 0; i < m; i++) {
        while (edge_idx < n - 1 && edges[edge_idx].w <= queries[i].q) {
            dsu.unite(edges[edge_idx].u, edges[edge_idx].v);
            edge_idx++;
        }
        ans[queries[i].id] = dsu.current_pairs;
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << (i == m - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
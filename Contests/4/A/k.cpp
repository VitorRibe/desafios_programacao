/*
K - Árvore Geradora Mínima

Encontre a árvore geradora mínima do grafo.

Entrada:
Na primeira linha haverá dois inteiros N - o número de nós e M - o número de arestas. (1 <= N <= 10000), (1 <= M <= 100000)
M linhas seguem com três inteiros i j k em cada linha representando uma aresta entre o nó i e j com peso k. Os IDs dos nós estão entre 1 e n inclusive. O peso de cada aresta será <= 1000000.

Saída:
Número único representando o peso total da árvore geradora mínima neste grafo. Haverá apenas uma MST possível.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    long long weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }
    
    sort(edges.begin(), edges.end());
    
    DSU dsu(n);
    long long mst_weight = 0;
    
    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            mst_weight += edge.weight;
        }
    }
    
    cout << mst_weight << "\n";
    
    return 0;
}
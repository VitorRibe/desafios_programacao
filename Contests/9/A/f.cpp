/*
F - Dark roads

Economizar dinheiro apagando estradas de Byteland, mas garantindo conectividade. Encontre o máximo de dinheiro economizado. (Problema de Árvore Geradora Mínima)

Entrada:
Vários casos. Cada começa com m e n (vértices e arestas). Termina com 0 0.
n linhas x, y, z (vértices e custo).

Saída:
Dinheiro economizado (Custo Total - Custo MST).
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m, n;
    while (cin >> m >> n && (m != 0 || n != 0)) {
        vector<Edge> edges(n);
        long long total_cost = 0;
        for (int i = 0; i < n; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
            total_cost += edges[i].w;
        }

        sort(edges.begin(), edges.end());
        DSU dsu(m);

        long long mst_cost = 0;
        for (auto edge : edges) {
            if (dsu.find(edge.u) != dsu.find(edge.v)) {
                dsu.unite(edge.u, edge.v);
                mst_cost += edge.w;
            }
        }

        cout << total_cost - mst_cost << "\n";
    }

    return 0;
}
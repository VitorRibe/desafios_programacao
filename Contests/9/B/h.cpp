/*
H - Traffic Flow

N interseções e M ruas com capacidades. O departamento precisa fechar o máximo de ruas, sem desconectar as interseções, de tal forma que a capacidade mínima das estradas restantes seja a maior possível.
Problema da Árvore Geradora Máxima (Maximum Spanning Tree), onde queremos o peso da menor aresta nessa árvore.

Entrada:
N casos. Cada com n, m.
M linhas u, v, c (capacidade). (0-indexed)

Saída:
Case #x: capacidade da menor estrada restante na MST Máxima.
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w > other.w;
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

void solve(int tc) {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges.begin(), edges.end());
    DSU dsu(n);

    int min_capacity = 1e9;
    for (auto edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            min_capacity = min(min_capacity, edge.w);
        }
    }

    cout << "Case #" << tc << ": " << min_capacity << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; i++) solve(i);
    }
    return 0;
}
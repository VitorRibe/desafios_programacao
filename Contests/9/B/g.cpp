/*
G - ACM Contest and Blackout

Encontrar a Árvore Geradora Mínima (MST) e a segunda melhor (Second Best MST).

Entrada:
T casos de teste.
N, M (escolas e conexões).
M linhas A, B, C (custo C).

Saída:
Para cada caso, S1 e S2 (menor e segunda menor MST).
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w, id;
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

void solve() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
    }

    sort(edges.begin(), edges.end());
    DSU dsu(n + 1);

    int mst_cost = 0;
    vector<int> mst_edges;
    int components = n;

    for (int i = 0; i < m; i++) {
        if (dsu.find(edges[i].u) != dsu.find(edges[i].v)) {
            dsu.unite(edges[i].u, edges[i].v);
            mst_cost += edges[i].w;
            mst_edges.push_back(i);
            components--;
        }
    }

    if (components > 1) {

    }

    int second_mst_cost = 1e9;

    for (int exclude_idx : mst_edges) {
        DSU dsu2(n + 1);
        int current_cost = 0;
        int comps = n;

        for (int i = 0; i < m; i++) {
            if (i == exclude_idx) continue;
            if (dsu2.find(edges[i].u) != dsu2.find(edges[i].v)) {
                dsu2.unite(edges[i].u, edges[i].v);
                current_cost += edges[i].w;
                comps--;
            }
        }

        if (comps == 1) {
            second_mst_cost = min(second_mst_cost, current_cost);
        }
    }

    cout << mst_cost << " " << second_mst_cost << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}
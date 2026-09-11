/*
E - Reparação de Estradas

Existem n cidades e m estradas entre elas. As condições são ruins e não podem ser usadas. Sua tarefa é reparar algumas estradas para que haja uma rota decente entre quaisquer duas cidades, com o custo total mais baixo possível.

Entrada:
A primeira linha tem dois inteiros n e m: o número de cidades e estradas.
Depois, há m linhas descrevendo as estradas com a, b (as cidades conectadas) e c (o custo de reparação).

Saída:
Imprima um inteiro: o custo total mínimo de reparação. Se não houver solução, imprima "IMPOSSIBLE".
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
        if (parent[i] == i)
            return i;
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
    long long total_cost = 0;
    int edges_used = 0;

    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            total_cost += edge.weight;
            edges_used++;
        }
    }

    if (edges_used == n - 1) {
        cout << total_cost << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
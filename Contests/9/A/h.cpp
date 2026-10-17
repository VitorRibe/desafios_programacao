/*
H - Shichikuji and Power Grid

Fornecer eletricidade para n cidades construindo estações ou fios.
Estação i custa c_i.
Fio entre i e j custa (k_i + k_j) * dist_manhattan.
Minimizar custo, indicar estações e conexões.
É equivalente a MST com vértice fantasma 0. Construir estação i é ligar 0 a i com peso c_i.

Entrada:
n.
n linhas (x_i, y_i).
c_1...c_n.
k_1...k_n.

Saída:
Custo mínimo.
Número de estações.
Índices das estações.
Número de conexões.
As conexões a b.
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    long long w;
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

    int n;
    if (!(cin >> n)) return 0;

    vector<pair<long long, long long>> coords(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> coords[i].first >> coords[i].second;
    }

    vector<long long> c(n + 1);
    for (int i = 1; i <= n; i++) cin >> c[i];

    vector<long long> k(n + 1);
    for (int i = 1; i <= n; i++) cin >> k[i];

    vector<Edge> edges;
    for (int i = 1; i <= n; i++) {
        edges.push_back({0, i, c[i]});
        for (int j = i + 1; j <= n; j++) {
            long long dist = abs(coords[i].first - coords[j].first) + abs(coords[i].second - coords[j].second);
            edges.push_back({i, j, (k[i] + k[j]) * dist});
        }
    }

    sort(edges.begin(), edges.end());
    DSU dsu(n + 1);

    long long min_cost = 0;
    vector<int> stations;
    vector<pair<int, int>> connections;

    for (auto edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            min_cost += edge.w;
            if (edge.u == 0) {
                stations.push_back(edge.v);
            } else {
                connections.push_back({edge.u, edge.v});
            }
        }
    }

    cout << min_cost << "\n";
    cout << stations.size() << "\n";
    for (int i = 0; i < stations.size(); i++) {
        cout << stations[i] << (i + 1 == stations.size() ? "" : " ");
    }
    cout << "\n";
    cout << connections.size() << "\n";
    for (auto p : connections) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}
/*
H - Encontrando Ciclo (Cycle Finding)

Encontre um ciclo negativo no grafo direcionado. Imprima YES e o ciclo, ou NO.

Entrada:
n, m.
m linhas a, b, c.

Saída:
YES e os vértices do ciclo, ou NO.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v;
    long long w;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<long long> dist(n + 1, 0); 
    vector<int> parent(n + 1, -1);
    int x = -1;

    for (int i = 0; i < n; i++) {
        x = -1;
        for (auto e : edges) {
            if (dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;
                x = e.v;
            }
        }
    }

    if (x == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            x = parent[x];
        }

        vector<int> cycle;
        for (int v = x;; v = parent[v]) {
            cycle.push_back(v);
            if (v == x && cycle.size() > 1) break;
        }

        reverse(cycle.begin(), cycle.end());
        for (int i = 0; i < cycle.size(); i++) {
            cout << cycle[i] << (i + 1 == cycle.size() ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
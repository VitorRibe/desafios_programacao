/*
I - Andando em Círculos!! (Going in Cycle!!)

Grafo direcionado ponderado. Encontre o ciclo com a menor média.
Média = soma dos pesos / número de arestas.

Entrada:
N casos de teste.
n, m.
m linhas a, b, c.

Saída:
Case #x: média mínima formatada com 2 casas decimais, ou "No cycle found.".
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

const double INF = 1e18;

struct Edge {
    int u, v;
    double w;
};

void solve(int tc) {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    auto check = [&](double mean) {
        vector<double> dist(n + 1, 0);
        for (int i = 0; i < n; i++) {
            bool relaxed = false;
            for (auto e : edges) {
                if (dist[e.u] + e.w - mean < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w - mean;
                    relaxed = true;
                }
            }
            if (!relaxed) return false;
            if (i == n - 1) return true; 
        }
        return false;
    };

    double L = 0.0, R = 1e8, ans = -1;
    bool found = false;

    if (!check(1e9)) {
        cout << "Case #" << tc << ": No cycle found.\n";
        return;
    }

    for (int i = 0; i < 60; i++) {
        double mid = (L + R) / 2;
        if (check(mid)) {
            ans = mid;
            R = mid;
            found = true;
        } else {
            L = mid;
        }
    }

    cout << "Case #" << tc << ": " << fixed << setprecision(2) << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        for (int i = 1; i <= t; i++) {
            solve(i);
        }
    }

    return 0;
}
/*
G - Rotas Mais Curtas II (Shortest Routes II)

n cidades e m estradas. Processe q consultas para encontrar o menor caminho entre a e b.

Entrada
n, m, q.
m linhas a, b, c (estrada).
q linhas a, b (consulta).

Saída
O menor caminho para cada consulta, ou -1 se não houver.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));
    
    for (int i = 1; i <= n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        if (dist[u][v] == INF) cout << -1 << "\n";
        else cout << dist[u][v] << "\n";
    }

    return 0;
}
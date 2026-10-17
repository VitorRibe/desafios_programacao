/*
E - Investigação (Investigation)

Encontre o preço mínimo da rota de 1 a n, número de rotas de preço mínimo, e os números mínimo e máximo de voos nessas rotas.

Entrada:
n, m.
m linhas a, b, c.

Saída:
4 inteiros: preço mínimo, número de rotas, mín voos, máx voos.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18;
const int MOD = 1e9 + 7;

struct Edge {
    int to;
    long long weight;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<long long> dist(n + 1, INF);
    vector<int> count(n + 1, 0);
    vector<int> min_f(n + 1, 0);
    vector<int> max_f(n + 1, 0);

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[1] = 0;
    count[1] = 1;
    pq.push({0, 1});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto edge : adj[u]) {
            int v = edge.to;
            long long w = edge.weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                count[v] = count[u];
                min_f[v] = min_f[u] + 1;
                max_f[v] = max_f[u] + 1;
                pq.push({dist[v], v});
            } else if (dist[u] + w == dist[v]) {
                count[v] = (count[v] + count[u]) % MOD;
                min_f[v] = min(min_f[v], min_f[u] + 1);
                max_f[v] = max(max_f[v], max_f[u] + 1);
            }
        }
    }

    cout << dist[n] << " " << count[n] << " " << min_f[n] << " " << max_f[n] << "\n";

    return 0;
}
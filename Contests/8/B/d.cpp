/*
D - Desconto de Voo (Flight Discount)

Encontre o preço mínimo da rota de Syrjälä para Metsälä. Você pode reduzir o preço de um único voo pela metade.

Entrada:
n, m (cidades, voos).
m linhas a, b, c (voo a->b com custo c).

Saída:
Preço mínimo.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    long long weight;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<Edge>> adj_fwd(n + 1);
    vector<vector<Edge>> adj_rev(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj_fwd[u].push_back({v, w});
        adj_rev[v].push_back({u, w});
    }

    auto dijkstra = [](int start, const vector<vector<Edge>>& adj, vector<long long>& dist) {
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        dist[start] = 0;
        pq.push({0, start});

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
                    pq.push({dist[v], v});
                }
            }
        }
    };

    vector<long long> dist1(n + 1, INF);
    vector<long long> distN(n + 1, INF);

    dijkstra(1, adj_fwd, dist1);
    dijkstra(n, adj_rev, distN);

    long long min_cost = INF;
    for (int u = 1; u <= n; u++) {
        if (dist1[u] == INF) continue;
        for (auto edge : adj_fwd[u]) {
            int v = edge.to;
            long long w = edge.weight;
            if (distN[v] != INF) {
                min_cost = min(min_cost, dist1[u] + distN[v] + w / 2);
            }
        }
    }

    cout << min_cost << "\n";

    return 0;
}
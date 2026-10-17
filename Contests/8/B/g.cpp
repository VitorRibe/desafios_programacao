/*
G - Rotas de Voo (Flight Routes)

Encontre as k rotas de voo mais curtas de Syrjälä para Metsälä.

Entrada:
n, m, k.
m linhas a, b, c.

Saída:
k inteiros com os preços das k rotas mais baratas.
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

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<priority_queue<long long>> dist(n + 1);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    pq.push({0, 1});
    dist[1].push(0);

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u].top()) continue;

        for (auto edge : adj[u]) {
            int v = edge.to;
            long long w = edge.weight;

            if (dist[v].size() < k) {
                dist[v].push(d + w);
                pq.push({d + w, v});
            } else if (d + w < dist[v].top()) {
                dist[v].pop();
                dist[v].push(d + w);
                pq.push({d + w, v});
            }
        }
    }

    vector<long long> ans;
    while (!dist[n].empty()) {
        ans.push_back(dist[n].top());
        dist[n].pop();
    }

    for (int i = k - 1; i >= 0; i--) {
        cout << ans[i] << (i == 0 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
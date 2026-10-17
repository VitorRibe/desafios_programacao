/*
F - Caminho Mínimo (Minimum Path)

Para cada vértice de 2 a n, encontre o peso mínimo do caminho do vértice 1 até ele. 
O peso de um caminho é a soma de suas arestas, menos o peso da aresta máxima, mais o peso da aresta mínima no caminho.

Entrada:
n, m.
m linhas u, v, w.

Saída:
n - 1 inteiros: peso mínimo para cada i (2 <= i <= n).
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

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

    vector<vector<Edge>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<vector<vector<long long>>> dist(n + 1, vector<vector<long long>>(2, vector<long long>(2, INF)));
    
    // pq stores: {dist, u, max_subtracted, min_added}
    priority_queue<tuple<long long, int, int, int>, vector<tuple<long long, int, int, int>>, greater<tuple<long long, int, int, int>>> pq;

    dist[1][0][0] = 0;
    pq.push({0, 1, 0, 0});

    while (!pq.empty()) {
        auto top_elem = pq.top();
        long long d = get<0>(top_elem);
        int u = get<1>(top_elem);
        int mx = get<2>(top_elem);
        int mn = get<3>(top_elem);
        pq.pop();

        if (d > dist[u][mx][mn]) continue;

        for (auto edge : adj[u]) {
            int v = edge.to;
            long long w = edge.weight;

            // Normal move
            if (dist[u][mx][mn] + w < dist[v][mx][mn]) {
                dist[v][mx][mn] = dist[u][mx][mn] + w;
                pq.push({dist[v][mx][mn], v, mx, mn});
            }
            
            // This edge is the max (subtract it)
            if (mx == 0) {
                if (dist[u][mx][mn] < dist[v][1][mn]) {
                    dist[v][1][mn] = dist[u][mx][mn];
                    pq.push({dist[v][1][mn], v, 1, mn});
                }
            }
            
            // This edge is the min (add it twice)
            if (mn == 0) {
                if (dist[u][mx][mn] + 2 * w < dist[v][mx][1]) {
                    dist[v][mx][1] = dist[u][mx][mn] + 2 * w;
                    pq.push({dist[v][mx][1], v, mx, 1});
                }
            }
            
            // This edge is BOTH max and min (add w, subtract w, add w => just add w)
            if (mx == 0 && mn == 0) {
                if (dist[u][0][0] + w < dist[v][1][1]) {
                    dist[v][1][1] = dist[u][0][0] + w;
                    pq.push({dist[v][1][1], v, 1, 1});
                }
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        cout << dist[i][1][1] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
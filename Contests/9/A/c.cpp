/*
C - Longest Flight Route

Voo grátis do vértice 1 (Syrjälä) até o n (Lehmälä) visitando o máximo de cidades possível. Sem ciclos.

Entrada:
n, m.
m linhas a, b.

Saída:
Número máximo de cidades na rota e a rota. IMPOSSIBLE se não houver rota.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    vector<int> in_degree(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    vector<int> dist(n + 1, -1e9);
    vector<int> parent(n + 1, -1);
    dist[1] = 1;

    for (int u : order) {
        if (dist[u] > 0) {
            for (int v : adj[u]) {
                if (dist[u] + 1 > dist[v]) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                }
            }
        }
    }

    if (dist[n] < 0) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << dist[n] << "\n";
        vector<int> path;
        int curr = n;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i] << (i == 0 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
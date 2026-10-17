/*
C - Rota da Mensagem (Message Route)

A rede de Syrjälä possui n computadores e m conexões. Sua tarefa é descobrir se Uolevi (1) pode enviar uma mensagem para Maija (n), e se for possível, qual o número mínimo de computadores na rota.

Entrada
n, m: computadores e conexões.
m linhas a, b: conexão entre a e b.

Saída
Se possível, imprima k (número mínimo de computadores) e a rota.
Se não, "IMPOSSIBLE".
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dist(n + 1, -1);
    vector<int> parent(n + 1, -1);
    queue<int> q;

    q.push(1);
    dist[1] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == n) break;

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (dist[n] == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << dist[n] << "\n";
        vector<int> path;
        int curr = n;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << (i + 1 == path.size() ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
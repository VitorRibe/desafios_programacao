/*
J - A Bug's Life

Bipartição de grafo para checar a hipótese de apenas 2 gêneros e interações apenas opostas.
Identificar "Suspicious bugs found!" (não bipartido) ou "No suspicious bugs found!" (bipartido).

Entrada:
Cenários.
bugs, interações.
linhas com os pares de interação.

Saída:
Scenario #i:
Mensagem respectiva.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void solve(int tc) {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> color(n + 1, -1);
    bool suspicious = false;

    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        suspicious = true;
                        break;
                    }
                }
                if (suspicious) break;
            }
        }
        if (suspicious) break;
    }

    cout << "Scenario #" << tc << ":\n";
    if (suspicious) {
        cout << "Suspicious bugs found!\n";
    } else {
        cout << "No suspicious bugs found!\n";
    }
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
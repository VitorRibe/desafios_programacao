/*
I - Bicoloring

Grafo conectado. Determinar se é bipartido (bicolorable).

Entrada:
Casos terminando com n=0.
n (nós de 0 a n-1).
l (arestas).
l pares.

Saída:
BICOLORABLE. ou NOT BICOLORABLE.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n && n != 0) {
        int l;
        cin >> l;
        vector<vector<int>> adj(n);
        for (int i = 0; i < l; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> color(n, -1);
        bool is_bipartite = true;

        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
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
                            is_bipartite = false;
                            break;
                        }
                    }
                    if (!is_bipartite) break;
                }
            }
            if (!is_bipartite) break;
        }

        if (is_bipartite) {
            cout << "BICOLORABLE.\n";
        } else {
            cout << "NOT BICOLORABLE.\n";
        }
    }

    return 0;
}
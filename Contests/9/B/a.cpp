/*
A - Flight Routes Check

Existem n cidades e m conexões de voo. Verifique se você pode viajar de qualquer cidade para qualquer outra.

Entrada:
n, m (cidades e voos).
m linhas a, b.

Saída:
YES se todas as rotas são possíveis.
NO caso contrário, e imprima duas cidades a e b tais que não se pode ir de a para b.
(Problema de Componentes Fortemente Conexos - SCC)
*/

#include <iostream>
#include <vector>

using namespace std;

void dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    vector<vector<int>> rev_adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    vector<bool> visited(n + 1, false);
    dfs(1, adj, visited);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << "NO\n";
            cout << 1 << " " << i << "\n";
            return 0;
        }
    }

    visited.assign(n + 1, false);
    dfs(1, rev_adj, visited);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cout << "NO\n";
            cout << i << " " << 1 << "\n";
            return 0;
        }
    }

    cout << "YES\n";

    return 0;
}
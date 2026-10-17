/*
K - Caminhada Matinal (Morning Walk)

Ajudar Kamal a determinar se é possível visitar todas as ruas de uma cidade exatamente uma vez num único passeio (Circuito Euleriano).

Entrada:
Vários casos de teste. Cada caso tem:
N (número de cruzamentos, de 0 a N-1).
R (número de ruas).
R linhas com c1, c2 (ruas bidirecionais).

Saída:
'Possible' se for possível percorrer todas as ruas exatamente uma vez (formando um circuito que começa e termina no mesmo nó), 'Not Possible' caso contrário.
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

void solve() {
    int n, r;
    while (cin >> n >> r) {
        vector<vector<int>> adj(n);
        vector<int> degree(n, 0);

        for (int i = 0; i < r; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            degree[u]++;
            degree[v]++;
        }

        if (r == 0) {
            cout << "Not Possible\n";
            continue;
        }

        bool possible = true;
    
        for (int i = 0; i < n; i++) {
            if (degree[i] % 2 != 0) {
                possible = false;
                break;
            }
        }

        if (!possible) {
            cout << "Not Possible\n";
            continue;
        }

        vector<bool> visited(n, false);
        int start_node = -1;
        for (int i = 0; i < n; i++) {
            if (degree[i] > 0) {
                start_node = i;
                break;
            }
        }

        if (start_node != -1) {
            dfs(start_node, adj, visited);
            for (int i = 0; i < n; i++) {
                if (degree[i] > 0 && !visited[i]) {
                    possible = false;
                    break;
                }
            }
        }

        if (possible) {
            cout << "Possible\n";
        } else {
            cout << "Not Possible\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
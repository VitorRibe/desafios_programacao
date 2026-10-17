/*
E - Viagem de Ida e Volta (Round Trip)

Byteland tem n cidades e m estradas. Projete uma viagem de ida e volta que comece em uma cidade, passe por duas ou mais outras cidades e retorne à cidade inicial.

Entrada
n, m.
m linhas a, b (estradas).

Saída
Primeiro k (número de cidades), depois k cidades em ordem. Se não houver, "IMPOSSIBLE".
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<int> parent;
vector<int> visited;
int cycle_start, cycle_end;

bool dfs(int v, int p) {
    visited[v] = 1;
    for (int u : adj[v]) {
        if (u == p) continue;
        if (visited[u]) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
        parent[u] = v;
        if (dfs(u, v)) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    parent.assign(n + 1, -1);
    visited.assign(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cycle_start = -1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && dfs(i, parent[i])) {
            break;
        }
    }

    if (cycle_start == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_start);
        
        cout << cycle.size() << "\n";
        for (int i = 0; i < cycle.size(); i++) {
            cout << cycle[i] << (i + 1 == cycle.size() ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
/*
D - Necessary Roads

Existem n cidades e m ruas bidirecionais conectando todas.
Uma estrada é "necessária" se removê-la desconecta o grafo. (Encontrar Pontes / Bridges).
Encontre todas as estradas necessárias.

Entrada:
n, m.
m linhas a, b.

Saída:
k (número de estradas).
k linhas com as estradas.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<int> tin, low;
int timer;
vector<pair<int, int>> bridges;
vector<bool> visited;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                bridges.push_back({min(v, to), max(v, to)});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    tin.assign(n + 1, -1);
    low.assign(n + 1, -1);
    visited.assign(n + 1, false);
    timer = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);

    cout << bridges.size() << "\n";
    for (auto b : bridges) {
        cout << b.first << " " << b.second << "\n";
    }

    return 0;
}
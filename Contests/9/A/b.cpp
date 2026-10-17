/*
B - Longest Path

Há um grafo direcionado G com N vértices e M arestas sem ciclos direcionados.
Encontre o comprimento do caminho direcionado mais longo em G. O comprimento é o número de arestas.

Entrada:
N, M.
M linhas com as arestas direcionadas de x_i para y_i.

Saída:
Comprimento do caminho mais longo.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dfs(int u, vector<vector<int>>& adj, vector<int>& dp) {
    if (dp[u] != -1) return dp[u];
    int max_len = 0;
    for (int v : adj[u]) {
        max_len = max(max_len, 1 + dfs(v, adj, dp));
    }
    return dp[u] = max_len;
}

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
    }

    vector<int> dp(n + 1, -1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dfs(i, adj, dp));
    }

    cout << ans << "\n";

    return 0;
}
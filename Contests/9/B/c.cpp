/*
C - Coin Collector

n salas com k_i moedas e m túneis. Qual é o número máximo de moedas coletadas escolhendo qualquer sala de início e fim?
Condensação de Grafo (SCC) + DP no DAG.

Entrada:
n, m.
k_1, ..., k_n.
m linhas a, b.

Saída:
Máximo de moedas.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void dfs1(int u, const vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v, adj, visited, st);
        }
    }
    st.push(u);
}

void dfs2(int u, const vector<vector<int>>& rev_adj, vector<int>& scc, int scc_id) {
    scc[u] = scc_id;
    for (int v : rev_adj[u]) {
        if (scc[v] == 0) {
            dfs2(v, rev_adj, scc, scc_id);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> coins(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> coins[i];
    }

    vector<vector<int>> adj(n + 1);
    vector<vector<int>> rev_adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    vector<bool> visited(n + 1, false);
    stack<int> st;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs1(i, adj, visited, st);
        }
    }

    vector<int> scc(n + 1, 0);
    int scc_id = 0;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (scc[u] == 0) {
            scc_id++;
            dfs2(u, rev_adj, scc, scc_id);
        }
    }

    vector<long long> scc_coins(scc_id + 1, 0);
    for (int i = 1; i <= n; i++) {
        scc_coins[scc[i]] += coins[i];
    }

    vector<vector<int>> scc_adj(scc_id + 1);
    vector<int> in_degree(scc_id + 1, 0);

    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            if (scc[u] != scc[v]) {
                scc_adj[scc[u]].push_back(scc[v]);
                in_degree[scc[v]]++;
            }
        }
    }

    vector<int> order;
    for (int i = 1; i <= scc_id; i++) {
         order.push_back(i);
    }

    vector<long long> dp(scc_id + 1, 0);
    long long max_coins = 0;

    for (int i = 1; i <= scc_id; i++) {
        int u = i;
        dp[u] += scc_coins[u];
        max_coins = max(max_coins, dp[u]);
        for (int v : scc_adj[u]) {
            dp[v] = max(dp[v], dp[u]);
        }
    }

    cout << max_coins << "\n";

    return 0;
}
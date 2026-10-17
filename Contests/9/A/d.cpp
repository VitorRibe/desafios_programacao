/*
D - Game Routes

De 1 a n, quantas maneiras existem para completar o jogo num DAG? Módulo 10^9+7.

Entrada:
n, m.
m linhas a, b.

Saída:
Número de maneiras modulo 10^9+7.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MOD = 1e9 + 7;

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

    vector<int> ways(n + 1, 0);
    ways[1] = 1;

    for (int u : order) {
        for (int v : adj[u]) {
            ways[v] = (ways[v] + ways[u]) % MOD;
        }
    }

    cout << ways[n] << "\n";

    return 0;
}
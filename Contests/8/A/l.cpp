/*
L - Quantos Caminhos? (How Many Paths?)

Grafo direcionado G, pode conter loops. Para cada vértice v, imprima:
0: sem caminho de 1 a v
1: apenas um caminho de 1 a v
2: mais de um caminho de 1 a v, mas finito
-1: infinitos caminhos de 1 a v

Entrada
t casos de teste.
Para cada, n (vértices) e m (arestas), seguido pelas m arestas.

Saída
Para cada caso, sequência de n inteiros indicando a resposta para cada vértice.
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

void dfs(int u, vector<vector<int>>& adj, vector<int>& state, vector<int>& ans, vector<int>& reachable) {
    state[u] = 1; 
    reachable.push_back(u);

    for (int v : adj[u]) {
        if (state[v] == 0) {
            ans[v] = max(ans[v], 1);
            dfs(v, adj, state, ans, reachable);
        } else if (state[v] == 1) {
            ans[v] = -1;
        } else if (state[v] == 2) {
            if (ans[v] != -1) ans[v] = 2;
        }
    }
    
    state[u] = 2; 
}

void dfs_inf(int u, vector<vector<int>>& adj, vector<bool>& vis_inf, vector<int>& ans) {
    vis_inf[u] = true;
    ans[u] = -1;
    for (int v : adj[u]) {
        if (!vis_inf[v]) {
            dfs_inf(v, adj, vis_inf, ans);
        }
    }
}

void dfs_multi(int u, vector<vector<int>>& adj, vector<bool>& vis_multi, vector<int>& ans) {
    vis_multi[u] = true;
    if (ans[u] != -1) ans[u] = 2;
    for (int v : adj[u]) {
        if (!vis_multi[v]) {
            dfs_multi(v, adj, vis_multi, ans);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<int> state(n + 1, 0);
    vector<int> ans(n + 1, 0);
    vector<int> reachable;

    ans[1] = 1;
    dfs(1, adj, state, ans, reachable);

    vector<bool> vis_inf(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (ans[i] == -1 && !vis_inf[i]) {
            dfs_inf(i, adj, vis_inf, ans);
        }
    }

    vector<int> in_degree(n + 1, 0);
    for (int u : reachable) {
        for (int v : adj[u]) {
            in_degree[v]++;
        }
    }

    vector<bool> vis_multi(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] > 1 && ans[i] != -1 && !vis_multi[i]) {
            dfs_multi(i, adj, vis_multi, ans);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
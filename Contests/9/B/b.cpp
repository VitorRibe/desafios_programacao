/*
B - Planets and Kingdoms

n planetas, m teletransportadores. Dois planetas estão no mesmo reino se e somente se existe uma rota de a para b e de b para a (Componentes Fortemente Conexos).
Determine o reino para cada planeta.

Entrada:
n, m.
m linhas a, b.

Saída:
k (número de reinos).
Para cada planeta, um rótulo entre 1 e k.
*/

#include <iostream>
#include <vector>
#include <stack>

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

void dfs2(int u, const vector<vector<int>>& rev_adj, vector<int>& kingdom, int k_id) {
    kingdom[u] = k_id;
    for (int v : rev_adj[u]) {
        if (kingdom[v] == 0) {
            dfs2(v, rev_adj, kingdom, k_id);
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
    stack<int> st;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs1(i, adj, visited, st);
        }
    }

    vector<int> kingdom(n + 1, 0);
    int k_id = 0;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (kingdom[u] == 0) {
            k_id++;
            dfs2(u, rev_adj, kingdom, k_id);
        }
    }

    cout << k_id << "\n";
    for (int i = 1; i <= n; i++) {
        cout << kingdom[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
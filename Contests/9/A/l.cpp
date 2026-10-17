/*
L - Entrega de Correio (Mail Delivery)

Encontrar uma rota (Circuito Euleriano) que comece e termine no correio (cruzamento 1) e passe por cada rua exatamente uma vez.

Entrada:
n, m (cruzamentos e ruas).
m linhas com a e b indicando uma rua bidirecional.

Saída:
A sequência de cruzamentos visitados. IMPOSSIBLE se não for possível.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> degree(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        degree[u]++;
        degree[v]++;
    }

    for (int i = 1; i <= n; i++) {
        if (degree[i] % 2 != 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    vector<int> path;
    stack<int> st;
    vector<bool> used_edge(m, false);
    
    vector<int> edge_idx(n + 1, 0);

    st.push(1);

    while (!st.empty()) {
        int u = st.top();
        bool found_edge = false;

        while (edge_idx[u] < adj[u].size()) {
            int v = adj[u][edge_idx[u]].first;
            int e_id = adj[u][edge_idx[u]].second;
            edge_idx[u]++;

            if (!used_edge[e_id]) {
                used_edge[e_id] = true;
                st.push(v);
                found_edge = true;
                break;
            }
        }

        if (!found_edge) {
            path.push_back(u);
            st.pop();
        }
    }

    if (path.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << (i + 1 == path.size() ? "" : " ");
    }
    cout << "\n";
    return 0;
}
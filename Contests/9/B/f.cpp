/*
F - Teleporters Path

Um jogo tem n níveis e m teletransportadores direcionados. Vença o jogo movendo de 1 a n usando cada teletransportador exatamente uma vez (Caminho Euleriano Direcionado).

Entrada:
n, m.
m linhas a, b.

Saída:
m + 1 inteiros com a sequência de níveis, ou "IMPOSSIBLE".
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> in_deg(n + 1, 0), out_deg(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        out_deg[u]++;
        in_deg[v]++;
    }

    bool possible = true;
    if (out_deg[1] - in_deg[1] != 1) possible = false;
    if (in_deg[n] - out_deg[n] != 1) possible = false;

    for (int i = 2; i <= n - 1; i++) {
        if (in_deg[i] != out_deg[i]) {
            possible = false;
        }
    }

    if (!possible) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> path;
    stack<int> st;
    vector<bool> used(m, false);
    vector<int> edge_idx(n + 1, 0);

    st.push(1);

    while (!st.empty()) {
        int u = st.top();
        bool found = false;

        while (edge_idx[u] < adj[u].size()) {
            int v = adj[u][edge_idx[u]].first;
            int id = adj[u][edge_idx[u]].second;
            edge_idx[u]++;

            if (!used[id]) {
                used[id] = true;
                st.push(v);
                found = true;
                break;
            }
        }

        if (!found) {
            path.push_back(u);
            st.pop();
        }
    }

    if (path.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << (i + 1 == path.size() ? "" : " ");
    }
    cout << "\n";

    return 0;
}
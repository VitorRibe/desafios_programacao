/*
A - Course Schedule

Você tem que completar n cursos. Existem m requisitos da forma "o curso a tem que ser completado antes do curso b".
Sua tarefa é encontrar uma ordem na qual você pode completar os cursos.

Entrada:
A primeira linha tem n e m.
m linhas seguintes têm a e b.

Saída:
Imprima uma ordem válida ou "IMPOSSIBLE".
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

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

    if (order.size() == n) {
        for (int i = 0; i < n; i++) {
            cout << order[i] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
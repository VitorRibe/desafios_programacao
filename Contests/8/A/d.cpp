/*
D - Construindo Equipes (Building Teams)

Existem n alunos na classe de Uolevi e m amizades. Divida-os em duas equipes sem que dois amigos fiquem na mesma equipe.

Entrada
n, m.
m linhas a, b (amizades).

Saída
Para cada aluno, "1" ou "2" dependendo da equipe. Se não houver solução, "IMPOSSIBLE".
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
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> team(n + 1, 0); 
    bool possible = true;

    for (int i = 1; i <= n; i++) {
        if (team[i] == 0) {
            queue<int> q;
            q.push(i);
            team[i] = 1;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (team[v] == 0) {
                        team[v] = (team[u] == 1) ? 2 : 1;
                        q.push(v);
                    } else if (team[v] == team[u]) {
                        possible = false;
                        break;
                    }
                }
                if (!possible) break;
            }
        }
        if (!possible) break;
    }

    if (!possible) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 1; i <= n; i++) {
            cout << team[i] << (i == n ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
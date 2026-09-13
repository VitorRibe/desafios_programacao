/*
B - Construindo Equipes (Building Teams)

Existem n alunos na turma de Uolevi, e m amizades entre eles. Sua tarefa é dividir os alunos em duas equipes de tal forma que dois alunos em uma equipe não sejam amigos. Você pode escolher livremente os tamanhos das equipes.

Entrada:
A primeira linha de entrada tem dois inteiros n e m: o número de alunos e amizades. Os alunos são numerados 1, 2, ..., n.
Em seguida, existem m linhas descrevendo as amizades. Cada linha tem dois inteiros a e b: alunos a e b são amigos.
Toda amizade é entre dois alunos diferentes. Você pode assumir que há no máximo uma amizade entre quaisquer dois alunos.

Saída:
Imprima um exemplo de como construir as equipes. Para cada aluno, imprima "1" ou "2" dependendo de qual equipe o aluno será atribuído. Você pode imprimir qualquer equipe válida.
Se não houver soluções, imprima "IMPOSSIBLE".
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
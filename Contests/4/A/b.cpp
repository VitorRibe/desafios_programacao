/*
B - Rota de Mensagem

A rede de Syrjälä tem n computadores e m conexões. Sua tarefa é descobrir se Uolevi pode enviar uma mensagem para Maija e, se for possível, qual é o número mínimo de computadores nessa rota.

Entrada:
A primeira linha tem dois inteiros n e m: o número de computadores e conexões. Os computadores são numerados 1, 2, ..., n. O computador de Uolevi é o 1 e o de Maija é o n.
Em seguida, existem m linhas descrevendo as conexões. Cada linha tem dois inteiros a e b: há uma conexão entre esses computadores.

Saída:
Se for possível enviar uma mensagem, imprima primeiro k: o número mínimo de computadores em uma rota válida. Depois disso, imprima um exemplo dessa rota.
Se não houver rotas, imprima "IMPOSSIBLE".
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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

    vector<int> dist(n + 1, -1);
    vector<int> parent(n + 1, -1);
    queue<int> q;

    dist[1] = 1;
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == n) break;

        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (dist[n] == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << dist[n] << "\n";
        vector<int> path;
        int curr = n;
        while (curr != -1) {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i] << (i + 1 == path.size() ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
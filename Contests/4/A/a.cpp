/*
A - Construindo Estradas

Byteland tem n cidades e m estradas entre elas. O objetivo é construir novas estradas para que haja uma rota entre quaisquer duas cidades.
Sua tarefa é descobrir o número mínimo de estradas necessárias e também determinar quais estradas devem ser construídas.

Entrada:
A primeira linha tem dois inteiros n e m: o número de cidades e estradas. As cidades são numeradas de 1, 2, ..., n.
Depois disso, há m linhas descrevendo as estradas. Cada linha tem dois inteiros a e b: há uma estrada entre essas cidades.
Uma estrada sempre conecta duas cidades diferentes, e há no máximo uma estrada entre quaisquer duas cidades.

Saída:
Primeiro imprima um inteiro k: o número de estradas necessárias.
Em seguida, imprima k linhas que descrevem as novas estradas. Você pode imprimir qualquer solução válida.
*/
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    visited.assign(n + 1, false);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> components;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            components.push_back(i);
            dfs(i);
        }
    }

    cout << components.size() - 1 << "\n";
    for (size_t i = 1; i < components.size(); i++) {
        cout << components[i - 1] << " " << components[i] << "\n";
    }

    return 0;
}
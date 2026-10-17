/*
I - Close Group

Dado um grafo não direcionado com N vértices (N <= 18).
Encontre o número mínimo de componentes conectados possíveis após remover 0 ou mais arestas para que a condição seja satisfeita:
Se dois vértices estão na mesma componente, existe uma aresta que os conecta (ou seja, cada componente é uma clique).
Problema de particionamento de vértices no mínimo número de cliques (Coloração de Grafo complementar ou particionamento de cliques com DP com bitmask).

Entrada:
N M.
M linhas A_i B_i.

Saída:
Número mínimo de cliques.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> adj(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u] |= (1 << v);
        adj[v] |= (1 << u);
    }

    for (int i = 0; i < n; i++) {
        adj[i] |= (1 << i);
    }

    int full_mask = (1 << n);
    vector<bool> is_clique(full_mask, false);

    for (int mask = 1; mask < full_mask; mask++) {
        bool clique = true;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                if ((adj[i] & mask) != mask) {
                    clique = false;
                    break;
                }
            }
        }
        is_clique[mask] = clique;
    }

    vector<int> dp(full_mask, 1e9);
    dp[0] = 0;

    for (int mask = 1; mask < full_mask; mask++) {
        for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
            if (is_clique[submask]) {
                dp[mask] = min(dp[mask], dp[mask ^ submask] + 1);
            }
        }
    }

    cout << dp[full_mask - 1] << "\n";

    return 0;
}
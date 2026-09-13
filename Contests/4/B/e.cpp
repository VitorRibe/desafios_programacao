/*
E - Cores Distintas (Distinct Colors)

Você recebe uma árvore enraizada consistindo de n nós, o nó 1 é a raiz. Cada nó tem uma cor.
Determine para cada nó o número de cores distintas em sua subárvore.

Entrada:
n, o número de nós.
c_1, ..., c_n, a cor de cada nó.
n-1 linhas descrevendo as arestas a b.

Saída:
n inteiros, o número de cores distintas na subárvore de 1 a n.
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int color[MAXN];
set<int> colors[MAXN];
int ans[MAXN];

void dfs(int u, int p) {
    colors[u].insert(color[u]);
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            if (colors[u].size() < colors[v].size()) {
                swap(colors[u], colors[v]);
            }
            for (int c : colors[v]) {
                colors[u].insert(c);
            }
            colors[v].clear();
        }
    }
    ans[u] = colors[u].size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
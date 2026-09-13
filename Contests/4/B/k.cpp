/*
K - Consultas de Novas Estradas

Existem n cidades em Byteland, mas nenhuma estrada entre elas. No entanto, a cada dia, uma nova estrada será construída. Haverá um total de m estradas.
Sua tarefa é processar q consultas da forma: "após quantos dias podemos viajar da cidade a para a cidade b pela primeira vez?"

Entrada:
A primeira linha de entrada tem três inteiros n, m e q: o número de cidades, estradas e consultas. As cidades são numeradas de 1 a n.
Depois disso, existem m linhas que descrevem as estradas na ordem em que são construídas. Cada linha tem dois inteiros a e b: haverá uma estrada entre as cidades a e b.
Finalmente, existem q linhas que descrevem as consultas. Cada linha tem dois inteiros a e b: queremos viajar da cidade a para a cidade b.

Saída:
Para cada consulta, imprima o número de dias, ou -1 se nunca for possível.

Restrições:
1 <= n, m, q <= 2 * 10^5
1 <= a, b <= n
*/

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 400005;
int parent_node[MAXN];
int val[MAXN];
int up[MAXN][20];
int depth[MAXN];
vector<int> adj[MAXN];

int find_set(int v) {
    if (v == parent_node[v]) return v;
    return parent_node[v] = find_set(parent_node[v]);
}

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i < 20; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : adj[u]) {
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int i = 19; i >= 0; i--) {
        if ((diff >> i) & 1) {
            u = up[u][i];
        }
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    for (int i = 1; i <= 2 * n; i++) {
        parent_node[i] = i;
        val[i] = 0;
    }

    int cnt = n;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        int root_u = find_set(u);
        int root_v = find_set(v);
        if (root_u != root_v) {
            cnt++;
            val[cnt] = i;
            parent_node[root_u] = cnt;
            parent_node[root_v] = cnt;
            adj[cnt].push_back(root_u);
            adj[cnt].push_back(root_v);
        }
    }

    for (int i = 1; i <= cnt; i++) {
        if (parent_node[i] == i) {
            dfs(i, i);
        }
    }

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        if (find_set(u) != find_set(v)) {
            cout << -1 << "\n";
        } else {
            cout << val[get_lca(u, v)] << "\n";
        }
    }

    return 0;
}
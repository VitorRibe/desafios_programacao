/*
L - Qpwoeirut e Vértices

Você recebe um grafo não direcionado conexo com n vértices e m arestas. Os vértices do grafo são numerados por inteiros de 1 a n e as arestas do grafo são numeradas por inteiros de 1 a m.
Sua tarefa é responder a q consultas, cada uma consistindo de dois inteiros l e r. A resposta para cada consulta é o menor inteiro não negativo k tal que a seguinte condição seja válida:
- Para todos os pares de inteiros (a, b) tais que l <= a <= b <= r, os vértices a e b são alcançáveis um a partir do outro usando apenas as primeiras k arestas (ou seja, arestas 1, 2, ..., k).

Entrada:
A primeira linha contém um único inteiro t (1 <= t <= 1000) — o número de casos de teste.
A primeira linha de cada caso de teste contém três inteiros n, m e q — o número de vértices, arestas e consultas, respectivamente.
Cada uma das próximas m linhas contém dois inteiros u_i e v_i — extremos da i-ésima aresta. É garantido que o grafo é conexo.
Cada uma das próximas q linhas contém dois inteiros l e r — descrições das consultas.

Saída:
Para cada caso de teste, imprima q inteiros — as respostas para as consultas.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
int parent_node[MAXN];
int val[MAXN];
int up[MAXN][20];
int depth[MAXN];
vector<int> adj[MAXN];
int st[MAXN][20];
int lg[MAXN];

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

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 1; i <= 2 * n; i++) {
        parent_node[i] = i;
        val[i] = 0;
        adj[i].clear();
        depth[i] = 0;
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

    for (int i = 1; i < n; i++) {
        st[i][0] = val[get_lca(i, i + 1)];
    }

    for (int j = 1; (1 << j) < n; j++) {
        for (int i = 1; i + (1 << j) - 1 < n; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        if (l == r) {
            cout << 0 << (i == q - 1 ? "" : " ");
        } else {
            int len = r - l;
            int j = lg[len];
            int ans = max(st[l][j], st[r - (1 << j)][j]);
            cout << ans << (i == q - 1 ? "" : " ");
        }
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    lg[1] = 0;
    for (int i = 2; i < MAXN; i++) {
        lg[i] = lg[i / 2] + 1;
    }

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
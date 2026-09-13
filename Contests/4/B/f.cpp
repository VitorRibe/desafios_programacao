/*
F - Lomsat gelral

Você recebe uma árvore enraizada no vértice 1. Cada vértice é colorido.
Uma cor c é dominante na subárvore de v se nenhuma outra cor aparece mais vezes.
Encontre a soma de todas as cores dominantes na subárvore de cada vértice v.

Entrada:
n, o número de vértices.
c_i, a cor do vértice i.
n-1 arestas.

Saída:
n inteiros — as somas das cores dominantes para cada vértice.
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int color[MAXN];
map<int, int> cnt[MAXN];
long long sum_dom[MAXN];
int max_freq[MAXN];

void dfs(int u, int p) {
    cnt[u][color[u]] = 1;
    max_freq[u] = 1;
    sum_dom[u] = color[u];

    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            
            // Heurística de fusão (Small-to-Large) para otimização O(N log^2 N)
            if (cnt[u].size() < cnt[v].size()) {
                swap(cnt[u], cnt[v]);
                max_freq[u] = max_freq[v];
                sum_dom[u] = sum_dom[v];
            }
            
            // C++11 compatível (substitui o structured binding do C++17)
            for (auto const& p_map : cnt[v]) {
                int col = p_map.first;
                int freq = p_map.second;
                
                cnt[u][col] += freq;
                
                if (cnt[u][col] > max_freq[u]) {
                    max_freq[u] = cnt[u][col];
                    sum_dom[u] = col;
                } else if (cnt[u][col] == max_freq[u]) {
                    sum_dom[u] += col;
                }
            }
            cnt[v].clear();
        }
    }
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
        cout << sum_dom[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
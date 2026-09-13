/*
D - O Número de Impostores (The Number of Imposters)

Theofanis joga "Among them" com n outros jogadores (todos chamados "Andreas").
Eles fazem m comentários do tipo "i j c" (jogador i diz que j é c, onde c é imposter ou crewmate).
Um impostor sempre mente, um tripulante sempre diz a verdade.
Encontre o número máximo possível de impostores, ou -1 se os comentários se contradizem.

Entrada:
t casos de teste. Cada um começa com n e m.
m linhas seguintes com i j c.

Saída:
O número máximo de impostores ou -1.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        string role;
        cin >> u >> v >> role;
        int type = (role == "imposter") ? 1 : 0;
        adj[u].push_back({v, type});
        adj[v].push_back({u, type});
    }

    vector<int> color(n + 1, -1);
    int max_imposters = 0;
    bool possible = true;

    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            vector<int> q;
            q.push_back(i);
            color[i] = 0;
            int count[2] = {0, 0};
            count[0]++;
            
            int head = 0;
            while (head < (int)q.size()) {
                int u = q[head++];
                for (auto edge : adj[u]) {
                    int v = edge.first;
                    int type = edge.second;
                    int next_color = color[u] ^ type;
                    
                    if (color[v] == -1) {
                        color[v] = next_color;
                        count[next_color]++;
                        q.push_back(v);
                    } else if (color[v] != next_color) {
                        possible = false;
                    }
                }
            }
            if (!possible) break;
            max_imposters += max(count[0], count[1]);
        }
    }

    if (!possible) {
        cout << -1 << "\n";
    } else {
        cout << max_imposters << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
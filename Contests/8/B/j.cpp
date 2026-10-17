/*
J - Rei (King)

Decida se existe uma sequência S que satisfaça um conjunto de restrições de desigualdade de soma de subsequências. 

Entrada:
n, m (comprimento da sequência e número de restrições).
m linhas com s_i, n_i, o_i (gt ou lt), k_i.
s_i + s_{i+1} + ... + s_{i+n_i} > k_i (se gt)
s_i + s_{i+1} + ... + s_{i+n_i} < k_i (se lt)
Termina com 0.

Saída:
'lamentable kingdom' se existe, 'successful conspiracy' se não existe.
Isso é um problema de sistema de diferenças. 
S_i = soma de a_1 a a_i.
S_{j} - S_{i-1} < k => S_j <= S_{i-1} + k - 1
S_{j} - S_{i-1} > k => S_{i-1} - S_j < -k => S_{i-1} <= S_j - k - 1
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    while (cin >> n && n != 0) {
        cin >> m;

        vector<Edge> edges;
        for (int i = 0; i < m; i++) {
            int s, len, k;
            string op;
            cin >> s >> len >> op >> k;
            
            int u = s - 1;
            int v = s + len;

            if (op == "gt") {
                // S_v - S_u > k => S_u - S_v < -k => S_u <= S_v - k - 1
                edges.push_back({v, u, -k - 1});
            } else {
                // S_v - S_u < k => S_v <= S_u + k - 1
                edges.push_back({u, v, k - 1});
            }
        }

        vector<int> dist(n + 1, 0);
        bool neg_cycle = false;

        for (int i = 0; i <= n + 1; i++) {
            bool relaxed = false;
            for (auto e : edges) {
                if (dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w;
                    relaxed = true;
                }
            }
            if (!relaxed) break;
            if (i == n + 1) neg_cycle = true;
        }

        if (neg_cycle) {
            cout << "successful conspiracy\n";
        } else {
            cout << "lamentable kingdom\n";
        }
    }

    return 0;
}
/*
K - Consultas de Planetas II (Planets Queries II)

Você está jogando um jogo com n planetas. Cada planeta tem um teletransportador para outro planeta (ou para si mesmo).
Você tem q consultas: "estou no planeta a e quero chegar ao planeta b, qual o número mínimo de teletransportes?"

Entrada:
n, q (número de planetas e consultas).
t_1, t_2, ..., t_n (destino do teletransportador do planeta i).
q linhas com a e b.

Saída:
Número mínimo de teletransportes ou -1 se não for possível.
*/

#include <iostream>
#include <vector>

using namespace std;

const int LOG = 20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<vector<int>> up(n + 1, vector<int>(LOG));
    vector<int> t(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        up[i][0] = t[i];
    }

    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }

    vector<int> dist(n + 1, -1);
    vector<int> cycle_id(n + 1, 0);
    vector<int> cycle_pos(n + 1, 0);
    vector<int> cycle_len;
    
    int current_cycle = 1;

    vector<int> state(n + 1, 0); 

    for (int i = 1; i <= n; i++) {
        if (state[i] == 0) {
            int curr = i;
            while (state[curr] == 0) {
                state[curr] = 1;
                curr = t[curr];
            }
            
            if (state[curr] == 1) {
                cycle_len.push_back(0);
                int cycle_start = curr;
                int pos = 0;
                do {
                    cycle_id[curr] = current_cycle;
                    cycle_pos[curr] = pos++;
                    dist[curr] = 0;
                    state[curr] = 2;
                    curr = t[curr];
                } while (curr != cycle_start);
                
                cycle_len.back() = pos;
                current_cycle++;
            }
            
            curr = i;
            while (state[curr] == 1) {
                state[curr] = 2;
                curr = t[curr];
            }
        }
    }

    auto get_dist = [&](auto& self, int u) -> void {
        if (dist[u] != -1) return;
        self(self, t[u]);
        dist[u] = dist[t[u]] + 1;
        cycle_id[u] = cycle_id[t[u]];
    };

    for (int i = 1; i <= n; i++) {
        if (dist[i] == -1) {
            get_dist(get_dist, i);
        }
    }

    auto advance = [&](int u, int k) {
        for (int j = 0; j < LOG; j++) {
            if ((k >> j) & 1) {
                u = up[u][j];
            }
        }
        return u;
    };

    while (q--) {
        int a, b;
        cin >> a >> b;

        if (cycle_id[a] != cycle_id[b]) {
            cout << -1 << "\n";
            continue;
        }

        if (dist[a] >= dist[b]) {
            int k = dist[a] - dist[b];
            int ancestor = advance(a, k);
            
            if (ancestor == b) {
                cout << k << "\n";
            } else if (dist[b] == 0) {
                // b is in the cycle
                int d = (cycle_pos[b] - cycle_pos[ancestor] + cycle_len[cycle_id[a] - 1]) % cycle_len[cycle_id[a] - 1];
                cout << k + d << "\n";
            } else {
                cout << -1 << "\n";
            }
        } else {
            cout << -1 << "\n";
        }
    }

    return 0;
}
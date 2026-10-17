/*
C - Labirinto (Labyrinth)

Começando em (r, c), você pode se mover no máximo x vezes para a esquerda e y vezes para a direita. Quantas células são alcançáveis?

Entrada:
n, m (linhas, colunas).
r, c (célula inicial).
x, y (max esq, max dir).
n linhas descrevendo o labirinto (. livre, * obstáculo).

Saída:
Número de células alcançáveis.
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int INF = 1e9;
const int dx[] = {-1, 1, 0, 0}; 
const int dy[] = {0, 0, -1, 1}; 

struct State {
    int r, c, l, r_moves;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    int sr, sc;
    cin >> sr >> sc;
    sr--; sc--;

    int max_l, max_r;
    cin >> max_l >> max_r;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    vector<vector<int>> dist_l(n, vector<int>(m, INF));
    deque<pair<int, int>> dq;

    dist_l[sr][sc] = 0;
    dq.push_back({sr, sc});

    int count = 0;

    while (!dq.empty()) {
        int r = dq.front().first;
        int c = dq.front().second;
        dq.pop_front();

        int used_l = dist_l[r][c];
        int used_r = used_l + (c - sc); 

        if (used_l > max_l || used_r > max_r) continue;
        
        count++;

        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i];
            int nc = c + dy[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == '.') {
                int cost = (i == 2) ? 1 : 0; 
                
                if (dist_l[r][c] + cost < dist_l[nr][nc]) {
                    dist_l[nr][nc] = dist_l[r][c] + cost;
                    if (cost == 0) {
                        dq.push_front({nr, nc});
                    } else {
                        dq.push_back({nr, nc});
                    }
                }
            }
        }
    }

    cout << count << "\n";

    return 0;
}
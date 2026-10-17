/*
B - Mago no Labirinto (Wizard in Maze)

O mago pode:
A: Mover para um quadrado adjacente de estrada.
B: Usar magia para se teleportar para uma estrada na área de 5x5 centrada nele.
Qual o número mínimo de vezes para usar a magia e chegar ao destino?

Entrada:
H, W (altura, largura).
Ch, Cw (início).
Dh, Dw (fim).
Grade HxW (. estrada, # parede).

Saída:
Número mínimo de magias ou -1.
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int INF = 1e9;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w;
    if (!(cin >> h >> w)) return 0;

    int ch, cw, dh, dw;
    cin >> ch >> cw >> dh >> dw;
    ch--; cw--; dh--; dw--;

    vector<string> grid(h);
    for (int i = 0; i < h; i++) {
        cin >> grid[i];
    }

    vector<vector<int>> dist(h, vector<int>(w, INF));
    deque<pair<int, int>> dq;

    dist[ch][cw] = 0;
    dq.push_back({ch, cw});

    while (!dq.empty()) {
        int r = dq.front().first;
        int c = dq.front().second;
        dq.pop_front();

        if (r == dh && c == dw) {
            cout << dist[dh][dw] << "\n";
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i];
            int nc = c + dy[i];
            if (nr >= 0 && nr < h && nc >= 0 && nc < w && grid[nr][nc] == '.') {
                if (dist[r][c] < dist[nr][nc]) {
                    dist[nr][nc] = dist[r][c];
                    dq.push_front({nr, nc});
                }
            }
        }

        for (int i = -2; i <= 2; i++) {
            for (int j = -2; j <= 2; j++) {
                int nr = r + i;
                int nc = c + j;
                if (nr >= 0 && nr < h && nc >= 0 && nc < w && grid[nr][nc] == '.') {
                    if (dist[r][c] + 1 < dist[nr][nc]) {
                        dist[nr][nc] = dist[r][c] + 1;
                        dq.push_back({nr, nc});
                    }
                }
            }
        }
    }

    cout << -1 << "\n";

    return 0;
}
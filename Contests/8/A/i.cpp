/*
I - Monstros (Monsters)

Você e alguns monstros estão num labirinto. Chegue à fronteira antes que algum monstro chegue até você. Imprima o caminho se possível.

Entrada
n, m.
n linhas de m caracteres (., #, A, M).

Saída
YES + comprimento + caminho (D, U, L, R) ou NO.
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const char dir_char[] = {'U', 'D', 'L', 'R'};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    int start_x = -1, start_y = -1;
    queue<pair<int, int>> q_monsters;
    vector<vector<int>> dist_m(n, vector<int>(m, 1e9));

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') {
                start_x = i;
                start_y = j;
            } else if (grid[i][j] == 'M') {
                q_monsters.push({i, j});
                dist_m[i][j] = 0;
            }
        }
    }

    while (!q_monsters.empty()) {
        int x = q_monsters.front().first;
        int y = q_monsters.front().second;
        q_monsters.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#' && dist_m[nx][ny] > dist_m[x][y] + 1) {
                dist_m[nx][ny] = dist_m[x][y] + 1;
                q_monsters.push({nx, ny});
            }
        }
    }

    queue<pair<int, int>> q_a;
    vector<vector<int>> dist_a(n, vector<int>(m, 1e9));
    vector<vector<int>> parent(n, vector<int>(m, -1));
    
    q_a.push({start_x, start_y});
    dist_a[start_x][start_y] = 0;

    int end_x = -1, end_y = -1;

    while (!q_a.empty()) {
        int x = q_a.front().first;
        int y = q_a.front().second;
        q_a.pop();

        if (x == 0 || x == n - 1 || y == 0 || y == m - 1) {
            end_x = x;
            end_y = y;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#' && dist_a[nx][ny] > dist_a[x][y] + 1) {
                if (dist_a[x][y] + 1 < dist_m[nx][ny]) {
                    dist_a[nx][ny] = dist_a[x][y] + 1;
                    parent[nx][ny] = i; 
                    q_a.push({nx, ny});
                }
            }
        }
    }

    if (end_x == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        cout << dist_a[end_x][end_y] << "\n";
        string path = "";
        int cx = end_x, cy = end_y;
        while (cx != start_x || cy != start_y) {
            int d = parent[cx][cy];
            path += dir_char[d];
            cx -= dx[d];
            cy -= dy[d];
        }
        reverse(path.begin(), path.end());
        cout << path << "\n";
    }

    return 0;
}
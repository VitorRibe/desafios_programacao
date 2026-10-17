/*
B - Labirinto (Labyrinth)

Você recebe o mapa de um labirinto e sua tarefa é encontrar um caminho do início ao fim. Você pode caminhar para a esquerda, direita, cima e baixo.

Entrada
A primeira linha de entrada tem dois inteiros n e m: a altura e a largura do mapa.
Em seguida, há n linhas de m caracteres descrevendo o labirinto. Cada caractere é . (piso), # (parede), A (início) ou B (fim). Existe exatamente um A e um B.

Saída
Primeiro imprima "YES", se houver um caminho, e "NO" caso contrário.
Se houver um caminho, imprima o comprimento do menor caminho e sua descrição como uma string consistindo dos caracteres L (esquerda), R (direita), U (cima) e D (baixo).
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
    int end_x = -1, end_y = -1;

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') {
                start_x = i;
                start_y = j;
            } else if (grid[i][j] == 'B') {
                end_x = i;
                end_y = j;
            }
        }
    }

    vector<vector<int>> dist(n, vector<int>(m, -1));
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    vector<vector<char>> p_dir(n, vector<char>(m, ' '));
    queue<pair<int, int>> q;

    q.push({start_x, start_y});
    dist[start_x][start_y] = 0;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (x == end_x && y == end_y) break;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                parent[nx][ny] = {x, y};
                p_dir[nx][ny] = dir_char[i];
                q.push({nx, ny});
            }
        }
    }

    if (dist[end_x][end_y] == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        cout << dist[end_x][end_y] << "\n";
        string path = "";
        int curr_x = end_x, curr_y = end_y;
        while (curr_x != start_x || curr_y != start_y) {
            path += p_dir[curr_x][curr_y];
            pair<int, int> p = parent[curr_x][curr_y];
            curr_x = p.first;
            curr_y = p.second;
        }
        reverse(path.begin(), path.end());
        cout << path << "\n";
    }

    return 0;
}
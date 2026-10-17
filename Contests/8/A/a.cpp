/*
A - Contando Quartos (Counting Rooms)

Você recebe o mapa de um prédio e sua tarefa é contar o número de quartos. O tamanho do mapa é n x m quadrados, e cada quadrado é piso ou parede. Você pode caminhar para a esquerda, direita, cima e baixo através dos quadrados de piso.

Entrada
A primeira linha de entrada tem dois inteiros n e m: a altura e a largura do mapa.
Em seguida, há n linhas de m caracteres descrevendo o mapa. Cada caractere é . (piso) ou # (parede).

Saída
Imprima um inteiro: o número de quartos.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void dfs(int i, int j, int n, int m, vector<string>& grid) {
    if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j] != '.') {
        return;
    }
    grid[i][j] = '#';
    dfs(i - 1, j, n, m, grid);
    dfs(i + 1, j, n, m, grid);
    dfs(i, j - 1, n, m, grid);
    dfs(i, j + 1, n, m, grid);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int rooms = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                rooms++;
                dfs(i, j, n, m, grid);
            }
        }
    }

    cout << rooms << "\n";

    return 0;
}
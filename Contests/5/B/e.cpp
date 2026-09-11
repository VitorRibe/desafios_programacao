/*
E - Consultas na Floresta II

Você recebe uma grade n x n representando o mapa de uma floresta. Cada quadrado é vazio ou possui uma árvore. Sua tarefa é processar q consultas dos seguintes tipos:
1. Mudar o estado (vazio/árvore) de um quadrado.
2. Quantas árvores existem dentro de um retângulo na floresta?

Entrada:
A primeira linha de entrada tem dois inteiros n e q: o tamanho da floresta e o número de consultas.
Então, existem n linhas descrevendo a floresta. Cada linha tem n caracteres: . é um quadrado vazio e * é uma árvore.
Finalmente, existem q linhas descrevendo as consultas. O formato de cada linha é ou "1 y x" ou "2 y1 x1 y2 x2".

Saída:
Imprima a resposta para cada consulta do segundo tipo.
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAXN = 1005;
int bit[MAXN][MAXN];
int n;

void add(int y, int x, int val) {
    for (int i = y; i <= n; i += i & -i) {
        for (int j = x; j <= n; j += j & -j) {
            bit[i][j] += val;
        }
    }
}

int query(int y, int x) {
    int sum = 0;
    for (int i = y; i > 0; i -= i & -i) {
        for (int j = x; j > 0; j -= j & -j) {
            sum += bit[i][j];
        }
    }
    return sum;
}

int query_rect(int y1, int x1, int y2, int x2) {
    return query(y2, x2) - query(y1 - 1, x2) - query(y2, x1 - 1) + query(y1 - 1, x1 - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    if (!(cin >> n >> q)) return 0;
    vector<string> grid(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> grid[i];
        grid[i] = " " + grid[i];
        for (int j = 1; j <= n; j++) {
            if (grid[i][j] == '*') {
                add(i, j, 1);
            }
        }
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int y, x;
            cin >> y >> x;
            if (grid[y][x] == '*') {
                add(y, x, -1);
                grid[y][x] = '.';
            } else {
                add(y, x, 1);
                grid[y][x] = '*';
            }
        } else {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            cout << query_rect(y1, x1, y2, x2) << "\n";
        }
    }
    return 0;
}
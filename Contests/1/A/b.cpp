/*
Problema: B - Forest Queries (CSES - 1652)

Você recebe uma grade n x n representando o mapa de uma floresta. Cada quadrado está vazio ou contém uma árvore. O quadrado superior esquerdo tem coordenadas (1, 1), e o quadrado inferior direito tem coordenadas (n, n).

Sua tarefa é processar q consultas da forma: quantas árvores estão dentro de um determinado retângulo na floresta?

Entrada
A primeira linha de entrada possui dois inteiros n e q: o tamanho da floresta e o número de consultas.
Em seguida, existem n linhas descrevendo a floresta. Cada linha tem n caracteres: . é um quadrado vazio e * é uma árvore.
Finalmente, existem q linhas descrevendo as consultas. Cada linha tem quatro inteiros y_1, x_1, y_2, x_2 correspondendo aos cantos de um retângulo.

Saída
Imprima o número de árvores dentro de cada retângulo.

Restrições
- 1 <= n <= 1000
- 1 <= q <= 2 * 10^5
- 1 <= y_1 <= y_2 <= n
- 1 <= x_1 <= x_2 <= n
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<vector<int>> p(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        string row;
        cin >> row;
        for (int j = 1; j <= n; ++j) {
            int tree = (row[j - 1] == '*') ? 1 : 0;
            p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + tree;
        }
    }

    for (int i = 0; i < q; ++i) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        int ans = p[y2][x2] - p[y1 - 1][x2] - p[y2][x1 - 1] + p[y1 - 1][x1 - 1];
        cout << ans << "\n";
    }

    return 0;
}
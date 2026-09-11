/*
B - Consultas na Floresta

Você recebe uma grade n x n representando o mapa de uma floresta. Cada quadrado está vazio ou contém uma árvore. O quadrado superior esquerdo tem coordenadas (1, 1) e o quadrado inferior direito tem coordenadas (n, n).
Sua tarefa é processar q consultas da forma: quantas árvores estão dentro de um determinado retângulo na floresta?

Entrada:
A primeira linha de entrada contém dois inteiros n e q: o tamanho da floresta e o número de consultas.
Em seguida, há n linhas descrevendo a floresta. Cada linha tem n caracteres: . é um quadrado vazio e * é uma árvore.
Finalmente, existem q linhas descrevendo as consultas. Cada linha possui quatro inteiros y1, x1, y2, x2 correspondendo aos cantos de um retângulo.

Saída:
Imprima o número de árvores dentro de cada retângulo.

Restrições:
1 <= n <= 1000
1 <= q <= 2 * 10^5
1 <= y1 <= y2 <= n
1 <= x1 <= x2 <= n
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int pref[1005][1005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= n; j++) {
            int val = (s[j - 1] == '*' ? 1 : 0);
            pref[i][j] = val + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        }
    }

    while (q--) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        int ans = pref[y2][x2] - pref[y1 - 1][x2] - pref[y2][x1 - 1] + pref[y1 - 1][x1 - 1];
        cout << ans << "\n";
    }

    return 0;
}
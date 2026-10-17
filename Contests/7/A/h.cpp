/*
H - Remainder Problem

É dado um arranjo a consistindo de 500000 inteiros (numerados de 1 a 500000). Inicialmente, todos os elementos de a são zero.

Você precisa processar dois tipos de consultas para este arranjo:
- 1 x y — aumentar a_x por y;
- 2 x y — calcular a soma de a_i para todos os i de 1 a 500000 que possuem resto y módulo x.

Você consegue processar todas as consultas?

Entrada:
A primeira linha contém um inteiro q (1 <= q <= 500000) — o número de consultas.
Em seguida, seguem q linhas, cada uma descrevendo uma consulta. A i-ésima linha contém três inteiros t_i, x_i e y_i (1 <= t_i <= 2). Se t_i = 1, então é uma consulta do primeiro tipo, 1 <= x_i <= 500000 e -1000 <= y_i <= 1000. Se t_i = 2, então é uma consulta do segundo tipo, 1 <= x_i <= 500000 e 0 <= y_i < x_i.
É garantido que haverá pelo menos uma consulta do tipo 2.

Saída:
Para cada consulta do tipo 2, imprima um inteiro — a resposta para ela.
*/

#include <iostream>

using namespace std;

const int MAXN = 500005;
const int BLK = 700;

int a[MAXN];
int ans[BLK + 5][BLK + 5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;

        if (type == 1) {
            a[x] += y;
            for (int i = 1; i <= BLK; i++) {
                ans[i][x % i] += y;
            }
        } else {
            if (x <= BLK) {
                cout << ans[x][y] << "\n";
            } else {
                int sum = 0;
                for (int i = y; i <= 500000; i += x) {
                    sum += a[i];
                }
                cout << sum << "\n";
            }
        }
    }

    return 0;
}
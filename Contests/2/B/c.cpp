/*
Problema: C - Static Range Minimum Queries (CSES - 1647)

Dado um array de n inteiros, sua tarefa é processar q consultas no formato: qual é o valor mínimo no intervalo [a, b]?

Entrada
A primeira linha de entrada possui dois inteiros n e q: o número de valores e consultas.
A segunda linha possui n inteiros x_1, x_2, ..., x_n: os valores do array.
Finalmente, existem q linhas descrevendo as consultas. Cada linha possui dois inteiros a e b: qual é o valor mínimo no intervalo [a, b]?

Saída
Imprima o resultado de cada consulta.

Restrições
- 1 <= n, q <= 2 * 10^5
- 1 <= x_i <= 10^9
- 1 <= a <= b <= n
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    int max_k = log2(n) + 1;
    vector<vector<int>> st(n, vector<int>(max_k));

    for (int i = 0; i < n; ++i) {
        cin >> st[i][0];
    }

    for (int j = 1; j < max_k; ++j) {
        for (int i = 0; i + (1 << j) <= n; ++i) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--; 
        r--;
        int k = log2(r - l + 1);
        cout << min(st[l][k], st[r - (1 << k) + 1][k]) << "\n";
    }

    return 0;
}
/*
Problema: G - Apartments (CSES - 1084)

Existem n candidatos e m apartamentos livres. Sua tarefa é distribuir os apartamentos para que o maior número possível de candidatos consiga um apartamento.

Cada candidato tem um tamanho de apartamento desejado, e eles aceitarão qualquer apartamento cujo tamanho seja próximo o suficiente do tamanho desejado.

Entrada
A primeira linha de entrada possui três inteiros n, m e k: o número de candidatos, o número de apartamentos e a diferença máxima permitida.
A próxima linha contém n inteiros a_1, a_2, ..., a_n: o tamanho desejado do apartamento de cada candidato. Se o tamanho desejado de um candidato for x, ele aceitará qualquer apartamento cujo tamanho esteja entre x - k e x + k.
A última linha contém m inteiros b_1, b_2, ..., b_m: o tamanho de cada apartamento.

Saída
Imprima um inteiro: o número de candidatos que conseguirão um apartamento.

Restrições
- 1 <= n, m <= 2 * 10^5
- 0 <= k <= 10^9
- 1 <= a_i, b_i <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    long long k;
    if (!(cin >> n >> m >> k)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<long long> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = 0;
    int j = 0;
    int ans = 0;

    while (i < n && j < m) {
        if (abs(a[i] - b[j]) <= k) {
            ans++;
            i++;
            j++;
        } else if (a[i] < b[j]) {
            i++;
        } else {
            j++;
        }
    }

    cout << ans << "\n";

    return 0;
}
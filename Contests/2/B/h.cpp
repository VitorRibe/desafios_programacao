/*
Problema: H - Subarray Divisibility (CSES - 1662)

Dado um array de n inteiros, sua tarefa é contar o número de subarrays onde a soma dos valores é divisível por n.

Entrada
A primeira linha de entrada possui um inteiro n: o tamanho do array.
A próxima linha possui n inteiros a_1, a_2, ..., a_n: os conteúdos do array.

Saída
Imprima um inteiro: o número necessário de subarrays.

Restrições
- 1 <= n <= 2 * 10^5
- -10^9 <= a_i <= 10^9
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    long long count = 0;
    long long prefix = 0;
    vector<int> mod_counts(n, 0);
    mod_counts[0] = 1;

    for (int i = 0; i < n; ++i) {
        long long a;
        cin >> a;
        prefix = (prefix + a % n + n) % n;
        count += mod_counts[prefix];
        mod_counts[prefix]++;
    }

    cout << count << "\n";

    return 0;
}
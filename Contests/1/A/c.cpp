/*
Problema: C - Maximum Subarray Sum (CSES - 1643)

Dado um array de n inteiros, sua tarefa é encontrar a soma máxima de valores em um subarray contíguo e não vazio.

Entrada
A primeira linha de entrada possui um inteiro n: o tamanho do array.
A segunda linha possui n inteiros x_1, x_2, ..., x_n: os valores do array.

Saída
Imprima um inteiro: a soma máxima do subarray.

Restrições
- 1 <= n <= 2 * 10^5
- -10^9 <= x_i <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    long long max_sum = -1e18;
    long long current_sum = -1e18;

    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        current_sum = max(x, current_sum + x);
        max_sum = max(max_sum, current_sum);
    }

    cout << max_sum << "\n";

    return 0;
}
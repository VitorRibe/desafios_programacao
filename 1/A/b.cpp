/*
Problema: B - Missing Number (CSES - 1083)

Você recebe todos os números entre 1, 2, ..., n, exceto um. Sua tarefa é encontrar o número que falta.

Entrada
A primeira linha de entrada contém um inteiro n.
A segunda linha contém n - 1 números. Cada número é distinto e está entre 1 e n (inclusive).

Saída
Imprima o número que falta.

Restrições
- 2 <= n <= 2 * 10^5
*/
#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;

    long long total_sum = n * (n + 1) / 2;
    long long current_sum = 0;

    for (int i = 0; i < n - 1; i++) {
        long long x;
        cin >> x;
        current_sum += x;
    }

    cout << total_sum - current_sum << "\n";

    return 0;
}
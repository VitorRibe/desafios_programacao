/*
C - Soma Máxima de Subvetor

Dado um array de n inteiros, sua tarefa é encontrar a soma máxima de valores em um subvetor contíguo e não vazio.

Entrada:
A primeira linha de entrada contém um inteiro n: o tamanho do array.
A segunda linha contém n inteiros x_1, x_2, ..., x_n: os valores do array.

Saída:
Imprima um inteiro: a soma máxima do subvetor.

Restrições:
1 <= n <= 2 * 10^5
-10^9 <= x_i <= 10^9
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

    long long max_so_far = -1e18;
    long long current_max = -1e18;

    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        if (i == 0) {
            current_max = x;
            max_so_far = x;
        } else {
            current_max = max(x, current_max + x);
            max_so_far = max(max_so_far, current_max);
        }
    }

    cout << max_so_far << "\n";

    return 0;
}
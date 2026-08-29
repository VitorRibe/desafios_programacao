/*
Problema: D - Increasing Array (CSES - 1094)

Você recebe um array de n inteiros. Você deseja modificar o array para que ele seja crescente, ou seja, cada elemento seja pelo menos tão grande quanto o elemento anterior.
A cada movimento, você pode aumentar o valor de qualquer elemento em um. Qual é o número mínimo de movimentos necessários?

Entrada
A primeira linha de entrada contém um inteiro n: o tamanho do array.
Então, a segunda linha contém n inteiros x_1, x_2, ..., x_n: o conteúdo do array.

Saída
Imprima o número mínimo de movimentos.

Restrições
- 1 <= n <= 2 * 10^5
- 1 <= x_i <= 10^9
*/
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    long long moves = 0;
    long long prev;
    cin >> prev;

    for (int i = 1; i < n; i++) {
        long long current;
        cin >> current;

        if (current < prev) {
            moves += (prev - current);
        } else {
            prev = current;
        }
    }

    cout << moves << "\n";

    return 0;
}
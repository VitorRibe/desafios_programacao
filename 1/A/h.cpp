/*
Problema: H - Trailing Zeros (CSES - 1618)

Sua tarefa é calcular o número de zeros finais no fatorial n!.

Por exemplo, 20! = 2432902008176640000 e tem 4 zeros finais.

Entrada
A única linha de entrada possui um inteiro n.

Saída
Imprima o número de zeros finais em n!.

Restrições
- 1 <= n <= 10^9
*/
#include <iostream>
using namespace std;

int main() {
    long long n;

    if (!(cin >> n)) return 0;

    long long zeros = 0;
    
    for (long long i = 5; n / i >= 1; i *= 5) {
        zeros += n / i;
    }
    cout << zeros << "\n";
    return 0;
}
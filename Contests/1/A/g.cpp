/*
Problema: G - Bit Strings (CSES - 1617)

Sua tarefa é calcular o número de cadeias de bits (bit strings) de comprimento n.

Por exemplo, se n = 3, a resposta correta é 8, porque as cadeias de bits possíveis são 000, 001, 010, 011, 100, 101, 110 e 111.

Entrada
A única linha de entrada possui um inteiro n.

Saída
Imprima o resultado módulo 10^9 + 7.

Restrições
- 1 <= n <= 10^6
*/
#include <iostream>
using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    long long ans = 1;
    long long MOD = 1000000007;

    for (int i = 0; i < n; i++) {
        ans = (ans * 2) % MOD;
    }
    cout << ans << "\n";
    return 0;
}
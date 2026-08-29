/*
Problema: E - Permutations (CSES - 1070)

Uma permutação dos inteiros 1, 2, ..., n é chamada de "beautiful" (linda) se não houver elementos adjacentes cuja diferença seja 1.
Dado n, construa uma permutação linda se tal permutação existir.

Entrada
A única linha de entrada contém um inteiro n.

Saída
Imprima uma permutação linda dos inteiros 1, 2, ..., n. Se houver várias soluções, você pode imprimir qualquer uma delas. Se não houver soluções, imprima "NO SOLUTION".

Restrições
- 1 <= n <= 10^6
*/
#include <iostream>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    if (n == 1) {
        cout << 1 << "\n";
        return 0;
    }

    if (n == 2 || n == 3) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    for (int i = 2; i <= n; i += 2) {
        cout << i << " ";
    }

    for (int i = 1; i <= n; i += 2) {
        cout << i << " ";
    }
    cout << "\n";
    return 0;
}
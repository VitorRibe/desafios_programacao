/*
Problema: F - Number Spiral (CSES - 1071)

Uma espiral de números é uma grade infinita cujo quadrado superior esquerdo tem o número 1. Sua tarefa é descobrir o número na linha y e coluna x.

Entrada
A primeira linha de entrada contém um inteiro t: o número de testes.
Depois disso, existem t linhas, cada uma contendo os inteiros y e x.

Saída
Para cada teste, imprima o número na linha y e coluna x.

Restrições
- 1 <= t <= 10^5
- 1 <= y, x <= 10^9
*/
#include <iostream>
#include <algorithm>

using namespace std;

void solve() {
    long long y, x;
    cin >> y >> x;

    long long z = max(y, x);
    long long z_sq = z * z;

    if (z % 2 == 0) {
        if (y == z) {
            cout << z_sq - (x - 1) << "\n";
        } else {
            cout << (z - 1) * (z - 1) + y << "\n";
        }
    } else {
        if (x == z) {
            cout << z_sq - (y - 1) << "\n";
        } else {
            cout << (z - 1) * (z - 1) + x << "\n";
        }
    }
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
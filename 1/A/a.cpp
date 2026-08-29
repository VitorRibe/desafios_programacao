/*
Problema: A - Weird Algorithm (CSES - 1068)

Considere um algoritmo que recebe como entrada um inteiro positivo n. Se n for par, o algoritmo 
o divide por dois, e se n for ímpar, o algoritmo o multiplica por três e soma um. O algoritmo 
repete isso até que n seja um. Por exemplo, a sequência para n = 3 é a seguinte:

3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1

Sua tarefa é simular a execução do algoritmo para um determinado valor de n.

Entrada
A única linha de entrada contém um inteiro n.

Saída
Imprima uma linha que contém todos os valores de n durante o algoritmo.

Restrições
- 1 <= n <= 10^6
*/
#include <iostream>

using namespace std;

int main() {
    long long n;
    cin >> n;
    while (n != 1) {
        cout << n << " ";
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = n * 3 + 1;
        }
    }
    cout << n << "\n";

    return 0;
}
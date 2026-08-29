/*
Problema: A - Stick Lengths (CSES - 1074)

Existem n gravetos com alguns comprimentos. Sua tarefa é modificar os gravetos para que cada um tenha o mesmo comprimento.

Você pode tanto aumentar quanto diminuir o comprimento de cada graveto. Ambas as operações custam x, onde x é a diferença entre o comprimento novo e o original.

Qual é o custo total mínimo?

Entrada
A primeira linha de entrada contém um inteiro n: o número de gravetos.
Depois há n inteiros p_1, p_2, ..., p_n: os comprimentos dos gravetos.

Saída
Imprima um inteiro: o custo total mínimo.

Restrições
- 1 <= n <= 2 * 10^5
- 1 <= p_i <= 10^9
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<long long> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    sort(p.begin(), p.end());

    long long median = p[n / 2];
    long long min_cost = 0;

    for (int i = 0; i < n; i++) {
        min_cost += abs(p[i] - median);
    }

    cout << min_cost << "\n";
    return 0;
}
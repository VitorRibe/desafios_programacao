/*
H - Comprimento das Varetas

Existem n varetas com determinados comprimentos. Sua tarefa é modificar as varetas para que todas tenham o mesmo comprimento.
Você pode aumentar ou diminuir o comprimento de cada vareta. Ambas as operações custam x, onde x é a diferença entre o novo comprimento e o comprimento original.
Qual é o custo total mínimo?

Entrada:
A primeira linha de entrada contém um inteiro n: o número de varetas.
Em seguida, há n inteiros p_1, p_2, ..., p_n: os comprimentos das varetas.

Saída:
Imprima um inteiro: o custo total mínimo.

Restrições:
1 <= n <= 2 * 10^5
1 <= p_i <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    sort(p.begin(), p.end());

    long long median = p[n / 2];
    long long total_cost = 0;

    for (int i = 0; i < n; i++) {
        total_cost += abs(p[i] - median);
    }

    cout << total_cost << "\n";

    return 0;
}
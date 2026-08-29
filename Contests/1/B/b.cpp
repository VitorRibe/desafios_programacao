/*
Problema: B - Ferris Wheel (CSES - 1090)

Existem n crianças que querem ir a uma roda-gigante, e sua tarefa é encontrar uma gôndola para cada criança.

Cada gôndola pode ter uma ou duas crianças e, além disso, o peso total em uma gôndola não pode exceder x. Você sabe o peso de cada criança.

Qual é o número mínimo de gôndolas necessárias para as crianças?

Entrada
A primeira linha de entrada contém dois inteiros n e x: o número de crianças e o peso máximo permitido.
A próxima linha contém n inteiros p_1, p_2, ..., p_n: o peso de cada criança.

Saída
Imprima um inteiro: o número mínimo de gôndolas.

Restrições
- 1 <= n <= 2 * 10^5
- 1 <= x <= 10^9
- 1 <= p_i <= x
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<long long> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    sort(p.begin(), p.end());

    int left = 0;
    int right = n - 1;
    int gondolas = 0;

    while (left <= right) {
        if (left == right) {
            gondolas++;
            break;
        }
        if (p[left] + p[right] <= x) {
            left++;
            right--;
            gondolas++;
        } else {
            right--;
            gondolas++;
        }
    }

    cout << gondolas << "\n";

    return 0;
}
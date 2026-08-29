/*
Problema: D - Sum of Two Values (CSES - 1640)

Você recebe um array de n inteiros, e sua tarefa é encontrar dois valores (em posições distintas) cuja soma é x.

Entrada
A primeira linha de entrada possui dois inteiros n e x: o tamanho do array e a soma alvo.
A segunda linha possui n inteiros a_1, a_2, ..., a_n: os valores do array.

Saída
Imprima dois inteiros: as posições dos valores. Se houver várias soluções, você pode imprimir qualquer uma delas. Se não houver soluções, imprima IMPOSSIBLE.

Restrições
- 1 <= n <= 2 * 10^5
- 1 <= x, a_i <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<pair<long long, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }

    sort(a.begin(), a.end());

    int left = 0;
    int right = n - 1;

    while (left < right) {
        long long current_sum = a[left].first + a[right].first;
        if (current_sum == x) {
            cout << a[left].second << " " << a[right].second << "\n";
            return 0;
        } else if (current_sum < x) {
            left++;
        } else {
            right--;
        }
    }

    cout << "IMPOSSIBLE\n";

    return 0;
}
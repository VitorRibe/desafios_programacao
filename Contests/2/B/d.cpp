/*
Problema: D - Maximum Subarray Sum II (CSES - 1644)

Dado um array de n inteiros, sua tarefa é encontrar a soma máxima de valores em um subarray contíguo com comprimento entre a e b.

Entrada
A primeira linha de entrada possui três inteiros n, a e b: o tamanho do array e o comprimento mínimo e máximo do subarray.
A segunda linha possui n inteiros x_1, x_2, ..., x_n: os valores do array.

Saída
Imprima um inteiro: a soma máxima do subarray.

Restrições
- 1 <= n <= 2 * 10^5
- 1 <= a <= b <= n
- -10^9 <= x_i <= 10^9
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b;
    if (!(cin >> n >> a >> b)) return 0;

    vector<long long> p(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        long long x;
        cin >> x;
        p[i] = p[i - 1] + x;
    }

    multiset<long long> ms;
    long long max_sum = -1e18;

    for (int i = a; i <= n; ++i) {
        ms.insert(p[i - a]);
        if (i > b) {
            ms.erase(ms.find(p[i - b - 1]));
        }
        max_sum = max(max_sum, p[i] - *ms.begin());
    }

    cout << max_sum << "\n";

    return 0;
}
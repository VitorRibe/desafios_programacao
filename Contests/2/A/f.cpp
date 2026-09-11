/*
F - Divisão de Array

Você recebe um array contendo n inteiros positivos.
Sua tarefa é dividir o array em k subvetores de modo que a soma máxima em um subvetor seja o menor possível.

Entrada:
A primeira linha de entrada contém dois inteiros n e k: o tamanho do array e o número de subvetores na divisão.
A próxima linha contém n inteiros x_1, x_2, ..., x_n: os elementos do array.

Saída:
Imprima um inteiro: a soma máxima em um subvetor na divisão ótima.

Restrições:
1 <= n <= 2 * 10^5
1 <= k <= n
1 <= x_i <= 10^9
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool check(long long max_sum, const vector<long long>& a, int k) {
    int count = 1;
    long long current_sum = 0;
    for (long long x : a) {
        if (current_sum + x > max_sum) {
            count++;
            current_sum = x;
        } else {
            current_sum += x;
        }
    }
    return count <= k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> a(n);
    long long low = 0, high = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        low = max(low, a[i]);
        high += a[i];
    }

    long long ans = high;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (check(mid, a, k)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
/*
Problema: F - Array Division (CSES - 1085)

Você recebe um array contendo n inteiros positivos.

Sua tarefa é dividir o array em k subarrays de modo que a soma máxima em um subarray seja a menor possível.

Entrada
A primeira linha de entrada contém dois inteiros n e k: o tamanho do array e o número de subarrays na divisão.
A próxima linha contém n inteiros x_1, x_2, ..., x_n: o conteúdo do array.

Saída
Imprima um inteiro: a soma máxima em um subarray na divisão ideal.

Restrições
- 1 <= n <= 2 * 10^5
- 1 <= k <= n
- 1 <= x_i <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> a(n);
    long long max_val = 0;
    long long sum_all = 0;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        max_val = max(max_val, a[i]);
        sum_all += a[i];
    }

    long long low = max_val;
    long long high = sum_all;
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        int subarrays = 1;
        long long current_sum = 0;

        for (int i = 0; i < n; ++i) {
            if (current_sum + a[i] > mid) {
                subarrays++;
                current_sum = a[i];
            } else {
                current_sum += a[i];
            }
        }

        if (subarrays <= k) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
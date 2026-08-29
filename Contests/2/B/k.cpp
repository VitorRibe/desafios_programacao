/*
Problema: K - Distinct Values Subarrays II (CSES - 2428)

Dado um array de n inteiros, sua tarefa é calcular o número de subarrays que têm no máximo k valores distintos.

Entrada
A primeira linha de entrada possui dois inteiros n e k.
A próxima linha possui n inteiros x_1, x_2, ..., x_n: os conteúdos do array.

Saída
Imprima um inteiro: o número de subarrays.

Restrições
- 1 <= k <= n <= 2 * 10^5
- 1 <= x_i <= 10^9
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    map<int, int> freq;
    long long ans = 0;
    int unique_count = 0;
    int left = 0;

    for (int right = 0; right < n; ++right) {
        if (freq[a[right]] == 0) {
            unique_count++;
        }
        freq[a[right]]++;

        while (unique_count > k) {
            freq[a[left]]--;
            if (freq[a[left]] == 0) {
                unique_count--;
            }
            left++;
        }

        ans += (right - left + 1);
    }

    cout << ans << "\n";

    return 0;
}
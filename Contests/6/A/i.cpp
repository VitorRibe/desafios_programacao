/*
I - Subvetores de Valores Distintos II (Distinct Values Subarrays II)

Dado um array de n inteiros, sua tarefa é calcular o número de subvetores que têm no máximo k valores distintos.

Entrada:
A primeira linha de entrada tem dois inteiros n e k.
A próxima linha tem n inteiros x_1, x_2, ..., x_n: os conteúdos do array.

Saída:
Imprima um inteiro: o número de subvetores.
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
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    map<int, int> counts;
    long long ans = 0;
    int l = 0;
    int distinct_count = 0;

    for (int r = 0; r < n; r++) {
        if (counts[a[r]] == 0) {
            distinct_count++;
        }
        counts[a[r]]++;

        while (distinct_count > k) {
            counts[a[l]]--;
            if (counts[a[l]] == 0) {
                distinct_count--;
            }
            l++;
        }

        ans += (r - l + 1);
    }

    cout << ans << "\n";

    return 0;
}
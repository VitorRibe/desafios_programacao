/*
Problema: G - Subarray Sums II (CSES - 1661)

Dado um array de n inteiros, sua tarefa é contar o número de subarrays cuja soma seja x.

Entrada
A primeira linha de entrada possui dois inteiros n e x: o tamanho do array e a soma alvo x.
A próxima linha possui n inteiros a_1, a_2, ..., a_n: os conteúdos do array.

Saída
Imprima um inteiro: o número necessário de subarrays.

Restrições
- 1 <= n <= 2 * 10^5
- -10^9 <= x, a_i <= 10^9
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    map<long long, int> prefix_counts;
    prefix_counts[0] = 1;

    long long current_sum = 0;
    long long count = 0;

    for (int i = 0; i < n; ++i) {
        long long val;
        cin >> val;
        current_sum += val;
        
        if (prefix_counts.count(current_sum - x)) {
            count += prefix_counts[current_sum - x];
        }
        
        prefix_counts[current_sum]++;
    }

    cout << count << "\n";

    return 0;
}
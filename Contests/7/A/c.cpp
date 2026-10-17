/*
C - Permutação

Dados N e K, encontre a N-ésima permutação dos inteiros de 1 a K quando essas permutações estão ordenadas lexicograficamente. N começa em 0. Como N é muito grande, N será representado por uma sequência de K inteiros não negativos S_1, S_2, ..., S_k. A partir desta sequência de inteiros, N pode ser calculado com a seguinte expressão:

sum_{i=1}^{K} S_i * (K - i)!

Entrada:
A primeira linha da entrada contém T (<= 10), o número de casos de teste. Cada um desses casos de teste consiste em 2 linhas. A primeira linha contém um inteiro K (1 <= K <= 50000). A próxima linha contém K inteiros S_1, S_2, ..., S_k (0 <= S_i <= K - i).

Saída:
Para cada caso de teste, a saída contém a N-ésima permutação dos inteiros de 1 a K. Esses K inteiros devem ser separados por um único espaço.
*/

#include <iostream>
#include <vector>

using namespace std;

int K;
vector<int> bit;

void update(int idx, int val) {
    for (; idx <= K; idx += idx & -idx) {
        bit[idx] += val;
    }
}

int find_kth(int k) {
    int pos = 0;
    for (int i = 1 << 16; i > 0; i >>= 1) {
        if (pos + i <= K && bit[pos + i] < k) {
            pos += i;
            k -= bit[pos];
        }
    }
    return pos + 1;
}

void solve() {
    cin >> K;
    bit.assign(K + 1, 0);

    for (int i = 1; i <= K; i++) {
        update(i, 1);
    }

    for (int i = 0; i < K; i++) {
        int s;
        cin >> s;
        int ans = find_kth(s + 1);
        update(ans, -1);
        cout << ans << (i == K - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
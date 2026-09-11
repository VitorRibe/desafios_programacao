/*
I - Vacas Agressivas

O fazendeiro John construiu um novo celeiro longo, com N baias. As baias estão localizadas ao longo de uma linha reta nas posições x_1 ... x_N.
Suas C vacas não gostam dessa disposição e tornam-se agressivas umas com as outras ao serem colocadas nas baias. Para evitar que as vacas se machuquem, FJ quer atribuir as vacas às baias de modo que a distância mínima entre duas vacas quaisquer seja o maior possível. Qual é a maior distância mínima possível?

Entrada:
t - o número de casos de teste, seguido pelos t casos de teste.
Linha 1: Dois inteiros separados por espaço: N e C (2 <= N <= 100000, 2 <= C <= N).
Linhas 2..N+1: A linha i+1 contém um número inteiro da posição da baia x_i (0 <= x_i <= 1000000000).

Saída:
Para cada caso de teste, imprima um inteiro: a maior distância mínima.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool can_place(const vector<long long>& x, int n, int c, long long dist) {
    int count = 1;
    long long last_pos = x[0];
    for (int i = 1; i < n; i++) {
        if (x[i] - last_pos >= dist) {
            count++;
            last_pos = x[i];
            if (count == c) return true;
        }
    }
    return count >= c;
}

void solve() {
    int n, c;
    cin >> n >> c;
    vector<long long> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    sort(x.begin(), x.end());

    long long low = 1, high = x[n - 1] - x[0];
    long long ans = 1;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (can_place(x, n, c, mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << ans << "\n";
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
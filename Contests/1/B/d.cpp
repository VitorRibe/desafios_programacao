/*
Problema: D - Movie Festival (CSES - 1629)

Em um festival de cinema, n filmes serão exibidos. Você sabe o horário de início e término de cada filme. Qual é o número máximo de filmes que você pode assistir por inteiro?

Entrada
A primeira linha de entrada possui um inteiro n: o número de filmes.
Depois disso, existem n linhas que descrevem os filmes. Cada linha possui dois inteiros a e b: os horários de início e término de um filme.

Saída
Imprima um inteiro: o número máximo de filmes.

Restrições
- 1 <= n <= 2 * 10^5
- 1 <= a < b <= 10^9
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<pair<int, int>> movies(n);
    for (int i = 0; i < n; i++) {
        cin >> movies[i].second >> movies[i].first;
    }

    sort(movies.begin(), movies.end());

    int count = 0;
    int current_end = 0;

    for (int i = 0; i < n; i++) {
        if (movies[i].second >= current_end) {
            count++;
            current_end = movies[i].first;
        }
    }

    cout << count << "\n";

    return 0;
}
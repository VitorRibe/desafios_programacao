/*
  Problema: J - Movie Festival
  
  Em um festival de cinema, n filmes serão exibidos. Você sabe o horário de início e término de cada filme.
  Qual é o número máximo de filmes que você pode assistir por inteiro?
  
  Entrada
  A primeira linha de entrada possui um inteiro n: o número de filmes.
  Depois disso, existem n linhas que descrevem os filmes. Cada linha possui dois inteiros a e b: 
  os horários de início e término de um filme.
  
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<pair<int, int>> movies(n);
    for (int i = 0; i < n; ++i) {
        cin >> movies[i].second >> movies[i].first; 
    }
    sort(movies.begin(), movies.end());

    int max_movies = 0;
    int current_end_time = 0;

    for (int i = 0; i < n; ++i) {
        if (movies[i].second >= current_end_time) {
            max_movies++;
            current_end_time = movies[i].first;
        }
    }
    cout << max_movies << "\n";
    return 0;
}
/*
  Problema: I - Sliding Window Median
  
  Você recebe um array de n inteiros. Sua tarefa é calcular a mediana de cada janela de k elementos, da esquerda para a direita.
  A mediana é o elemento do meio quando os elementos estão ordenados. Se o número de elementos for par, 
  existem duas medianas possíveis e assumimos que a mediana é a menor delas.
  
  Entrada
  A primeira linha contém dois inteiros n e k: o número de elementos e o tamanho da janela.
  Depois há n inteiros x_1, x_2, ..., x_n: os conteúdos do array.
  
  Saída
  Imprima n - k + 1 valores: as medianas.
  
  Restrições
  - 1 <= k <= n <= 2 * 10^5
  - 1 <= x_i <= 10^9
 */
#include <iostream>
#include <vector>
#include <set>

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

    set<pair<int, int>> left_set, right_set;

    auto balance = [&]() {
        while (left_set.size() > right_set.size() + 1) {
            auto it = prev(left_set.end());
            right_set.insert(*it);
            left_set.erase(it);
        }
        while (left_set.size() < right_set.size()) {
            auto it = right_set.begin();
            left_set.insert(*it);
            right_set.erase(it);
        }
    };

    auto add = [&](pair<int, int> p) {
        if (!left_set.empty() && p < *prev(left_set.end())) {
            left_set.insert(p);
        } else {
            right_set.insert(p);
        }
        balance();
    };

    auto remove = [&](pair<int, int> p) {
        if (left_set.count(p)) {
            left_set.erase(p);
        } else {
            right_set.erase(p);
        }
        balance();
    };

    for (int i = 0; i < k; ++i) {
        add({a[i], i});
    }

    cout << prev(left_set.end())->first;

    for (int i = k; i < n; ++i) {
        remove({a[i - k], i - k});
        add({a[i], i});
        cout << " " << prev(left_set.end())->first;
    }
    cout << "\n";
    return 0;
}
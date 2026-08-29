/*
Problema: J - Sliding Window Cost (CSES - 1077)

Você recebe um array de n inteiros. Sua tarefa é calcular para cada janela de k elementos, da esquerda para a direita, o custo total mínimo de tornar todos os elementos iguais.

Você pode aumentar ou diminuir cada elemento com custo x, onde x é a diferença entre o novo valor e o original. O custo total é a soma de tais custos.

Entrada
A primeira linha contém dois inteiros n e k: o número de elementos e o tamanho da janela.
Depois há n inteiros x_1, x_2, ..., x_n: os conteúdos do array.

Saída
Imprima n - k + 1 valores: os custos.

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

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    set<pair<long long, int>> left_set, right_set;
    long long left_sum = 0, right_sum = 0;

    auto balance = [&]() {
        size_t target_left = (k + 1) / 2;
        while (left_set.size() > target_left) {
            auto it = prev(left_set.end());
            right_sum += it->first;
            left_sum -= it->first;
            right_set.insert(*it);
            left_set.erase(it);
        }
        while (left_set.size() < target_left && !right_set.empty()) {
            auto it = right_set.begin();
            left_sum += it->first;
            right_sum -= it->first;
            left_set.insert(*it);
            right_set.erase(it);
        }
    };

    auto add = [&](pair<long long, int> p) {
        if (left_set.empty() || p < *left_set.rbegin()) {
            left_sum += p.first;
            left_set.insert(p);
        } else {
            right_sum += p.first;
            right_set.insert(p);
        }
        balance();
    };

    auto remove = [&](pair<long long, int> p) {
        if (left_set.count(p)) {
            left_sum -= p.first;
            left_set.erase(p);
        } else {
            right_sum -= p.first;
            right_set.erase(p);
        }
        balance();
    };

    for (int i = 0; i < k; ++i) {
        add({a[i], i});
    }

    long long median = left_set.rbegin()->first;
    long long cost = (median * left_set.size() - left_sum) + (right_sum - median * right_set.size());
    cout << cost;

    for (int i = k; i < n; ++i) {
        remove({a[i - k], i - k});
        add({a[i], i});
        median = left_set.rbegin()->first;
        cost = (median * left_set.size() - left_sum) + (right_sum - median * right_set.size());
        cout << " " << cost;
    }
    cout << "\n";

    return 0;
}
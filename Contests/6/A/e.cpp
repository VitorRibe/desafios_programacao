/*
E - Custo da Janela Deslizante

Você recebe um array de n inteiros. Sua tarefa é calcular para cada janela de k elementos, da esquerda para a direita, o custo total mínimo para tornar todos os elementos iguais.

Você pode aumentar ou diminuir cada elemento com custo x, onde x é a diferença entre o valor novo e o original. O custo total é a soma desses custos.

Entrada:
A primeira linha contém dois inteiros n e k: o número de elementos e o tamanho da janela.
Em seguida, há n inteiros x_1, x_2, ..., x_n: os conteúdos do array.

Saída:
Imprima n - k + 1 valores: os custos.
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

multiset<long long> low, high;
long long sum_low = 0, sum_high = 0;

void balance() {
    while (low.size() > high.size() + 1) {
        auto it = prev(low.end());
        sum_high += *it;
        sum_low -= *it;
        high.insert(*it);
        low.erase(it);
    }
    while (high.size() > low.size()) {
        auto it = high.begin();
        sum_low += *it;
        sum_high -= *it;
        low.insert(*it);
        high.erase(it);
    }
}

void insert_val(long long val) {
    if (low.empty() || val <= *low.rbegin()) {
        low.insert(val);
        sum_low += val;
    } else {
        high.insert(val);
        sum_high += val;
    }
    balance();
}

void erase_val(long long val) {
    auto it = low.find(val);
    if (it != low.end()) {
        sum_low -= val;
        low.erase(it);
    } else {
        it = high.find(val);
        sum_high -= val;
        high.erase(it);
    }
    balance();
}

long long get_cost() {
    long long median = *low.rbegin();
    return sum_high - sum_low + median * ((long long)low.size() - (long long)high.size());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < k; i++) {
        insert_val(a[i]);
    }

    cout << get_cost();

    for (int i = k; i < n; i++) {
        erase_val(a[i - k]);
        insert_val(a[i]);
        cout << " " << get_cost();
    }
    cout << "\n";

    return 0;
}
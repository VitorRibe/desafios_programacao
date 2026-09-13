/*
D - Mediana de Janela Deslizante (Sliding Window Median)

Você recebe um array de n inteiros. Sua tarefa é calcular a mediana de cada janela de k elementos, da esquerda para a direita.
A mediana é o elemento do meio quando os elementos são ordenados. Se o número de elementos for par, existem duas medianas possíveis e assumimos que a mediana é a menor delas.

Entrada:
A primeira linha contém dois inteiros n e k: o número de elementos e o tamanho da janela.
Em seguida, há n inteiros x_1, x_2, ..., x_n: os conteúdos do array.

Saída:
Imprima n - k + 1 valores: as medianas.
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

multiset<int> low, high;

void balance() {
    while (low.size() > high.size() + 1) {
        auto it = prev(low.end());
        high.insert(*it);
        low.erase(it);
    }
    while (high.size() > low.size()) {
        auto it = high.begin();
        low.insert(*it);
        high.erase(it);
    }
}

void insert_val(int val) {
    if (low.empty() || val <= *low.rbegin()) {
        low.insert(val);
    } else {
        high.insert(val);
    }
    balance();
}

void erase_val(int val) {
    auto it = low.find(val);
    if (it != low.end()) {
        low.erase(it);
    } else {
        high.erase(high.find(val));
    }
    balance();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < k; i++) {
        insert_val(a[i]);
    }

    cout << *low.rbegin();

    for (int i = k; i < n; i++) {
        erase_val(a[i - k]);
        insert_val(a[i]);
        cout << " " << *low.rbegin();
    }
    cout << "\n";

    return 0;
}
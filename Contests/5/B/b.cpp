/*
B - Remoções de Lista

Você recebe uma lista consistindo de n inteiros. Sua tarefa é remover elementos da lista em posições dadas, e relatar os elementos removidos.

Entrada:
A primeira linha de entrada tem um inteiro n: o tamanho inicial da lista. Durante o processo, os elementos são numerados 1, 2, ..., k onde k é o tamanho atual da lista.
A segunda linha tem n inteiros x_1, x_2, ..., x_n: o conteúdo da lista.
A última linha tem n inteiros p_1, p_2, ..., p_n: as posições dos elementos a serem removidos.

Saída:
Imprima os elementos na ordem em que são removidos.
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
int bit[MAXN];

void add(int i, int delta, int n) {
    for (; i <= n; i += i & -i) {
        bit[i] += delta;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        add(i, 1, n);
    }
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        int pos = 0;
        for (int j = 17; j >= 0; j--) {
            if (pos + (1 << j) <= n && bit[pos + (1 << j)] < p) {
                pos += (1 << j);
                p -= bit[pos];
            }
        }
        pos++;
        cout << a[pos] << (i == n ? "" : " ");
        add(pos, -1, n);
    }
    cout << "\n";
    return 0;
}
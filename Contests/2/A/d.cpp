/*
D - Soma de Dois Valores

Você recebe um array de n inteiros e sua tarefa é encontrar dois valores (em posições distintas) cuja soma seja x.

Entrada:
A primeira linha de entrada contém dois inteiros n e x: o tamanho do array e a soma alvo.
A segunda linha contém n inteiros a_1, a_2, ..., a_n: os valores do array.

Saída:
Imprima dois inteiros: as posições dos valores. Se existirem várias soluções, você pode imprimir qualquer uma delas. Se não existirem soluções, imprima IMPOSSIBLE.

Restrições:
1 <= n <= 2 * 10^5
1 <= x, a_i <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Element {
    long long val;
    int pos;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<Element> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].val;
        a[i].pos = i + 1;
    }

    sort(a.begin(), a.end(), [](const Element& left, const Element& right) {
        return left.val < right.val;
    });

    int l = 0, r = n - 1;
    while (l < r) {
        long long sum = a[l].val + a[r].val;
        if (sum == x) {
            cout << a[l].pos << " " << a[r].pos << "\n";
            return 0;
        }
        if (sum < x) {
            l++;
        } else {
            r--;
        }
    }

    cout << "IMPOSSIBLE\n";

    return 0;
}
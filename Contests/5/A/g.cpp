/*
G - O problema de Pashmak e Parmida

Parmida é uma garota inteligente e quer participar de Olimpíadas este ano. Claro que ela quer que seu parceiro também seja inteligente (embora ele não seja)! Parmida preparou o seguinte problema de teste para Pashmak.

Existe uma sequência a que consiste em n inteiros a_1, a_2, ..., a_n. Vamos denotar f(l, r, x) como o número de índices k tais que: l <= k <= r e a_k = x. A tarefa dele é calcular o número de pares de índices i, j (1 <= i < j <= n) tais que f(1, i, a_i) > f(j, n, a_j).

Ajude Pashmak com o teste.

Entrada:
A primeira linha da entrada contém um número inteiro n (1 <= n <= 10^6). A segunda linha contém n inteiros separados por espaço a_1, a_2, ..., a_n (1 <= a_i <= 10^9).

Saída:
Imprima um único inteiro — a resposta para o problema.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct FenwickTree {
    int n;
    vector<int> tree;

    FenwickTree(int n) {
        this->n = n;
        tree.assign(n + 1, 0);
    }

    void add(int i, int delta) {
        for (; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }

    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    vector<int> vals(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        vals[i] = a[i];
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    auto get_id = [&](int x) {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
    };

    vector<int> L(n), R(n);
    vector<int> count(vals.size() + 1, 0);

    for (int i = 0; i < n; i++) {
        int id = get_id(a[i]);
        count[id]++;
        L[i] = count[id];
    }

    fill(count.begin(), count.end(), 0);
    FenwickTree bit(n);

    for (int i = n - 1; i >= 0; i--) {
        int id = get_id(a[i]);
        count[id]++;
        R[i] = count[id];
        bit.add(R[i], 1);
    }

    long long ans = 0;
    for (int i = 0; i < n; i++) {
        bit.add(R[i], -1);
        ans += bit.query(L[i] - 1);
    }

    cout << ans << "\n";

    return 0;
}
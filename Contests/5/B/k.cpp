/*
K - K-consulta

Dada uma sequência de n números a_1, a_2 ... a_n e um número de k-consultas. Uma k-consulta é uma tripla (i, j, k) (1 <= i <= j <= n). Para cada k-consulta (i, j, k), você deve retornar o número de elementos maiores que k na subsequência a_i, a_{i+1} ... a_j.

Entrada:
A primeira linha contém n (1 <= n <= 30000).
A segunda linha contém n números a_1, a_2 ... a_n (1 <= a_i <= 10^9).
A terceira linha contém q (1 <= q <= 200000), o número de k-consultas.
Nas próximas q linhas, cada linha contém 3 números i, j, k representando uma k-consulta (1 <= i <= j <= n, 1 <= k <= 10^9).

Saída:
Para cada k-consulta (i, j, k), imprima o número de elementos maiores que k na subsequência a_i, a_{i+1} ... a_j em uma única linha.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Element {
    int val, id;
    bool operator<(const Element& other) const {
        return val > other.val;
    }
};

struct Query {
    int l, r, k, id;
    bool operator<(const Query& other) const {
        return k > other.k;
    }
};

const int MAXN = 30005;
int bit[MAXN];
int n;

void add(int i, int delta) {
    for (; i <= n; i += i & -i) {
        bit[i] += delta;
    }
}

int query(int i) {
    int sum = 0;
    for (; i > 0; i -= i & -i) {
        sum += bit[i];
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    vector<Element> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].val;
        a[i].id = i + 1;
    }

    sort(a.begin(), a.end());

    int q;
    cin >> q;
    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r >> queries[i].k;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end());

    vector<int> ans(q);
    int ptr = 0;

    for (int i = 0; i < q; ++i) {
        while (ptr < n && a[ptr].val > queries[i].k) {
            add(a[ptr].id, 1);
            ptr++;
        }
        ans[queries[i].id] = query(queries[i].r) - query(queries[i].l - 1);
    }

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}
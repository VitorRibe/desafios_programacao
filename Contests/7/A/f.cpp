/*
F - K-query

Dada uma sequência de n números a_1, a_2 ... a_n e um número de k-consultas. Uma k-consulta é uma tripla (i, j, k) (1 <= i <= j <= n). Para cada k-consulta (i, j, k), você deve retornar o número de elementos maiores que k na subsequência a_i, a_{i+1} ... a_j.

Entrada:
- Linha 1: n (1 <= n <= 30000).
- Linha 2: n números a_1, a_2 ... a_n (1 <= a_i <= 10^9).
- Linha 3: q (1 <= q <= 200000), o número de k-consultas.
- Nas próximas q linhas, cada linha contém 3 números i, j, k representando uma k-consulta (1 <= i <= j <= n, 1 <= k <= 10^9).

Saída:
- Para cada k-consulta (i, j, k), imprima o número de elementos maiores que k na subsequência a_i, a_{i+1} ... a_j em uma única linha.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Element {
    int val;
    int pos;

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

int n;
vector<int> bit;

void update(int idx, int val) {
    for (; idx <= n; idx += idx & -idx) {
        bit[idx] += val;
    }
}

int queryBIT(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += bit[idx];
    }
    return sum;
}

int queryRange(int l, int r) {
    return queryBIT(r) - queryBIT(l - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    vector<Element> elements(n);
    for (int i = 0; i < n; i++) {
        cin >> elements[i].val;
        elements[i].pos = i + 1;
    }

    int q;
    cin >> q;

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r >> queries[i].k;
        queries[i].id = i;
    }

    sort(elements.begin(), elements.end());
    sort(queries.begin(), queries.end());

    bit.assign(n + 1, 0);
    vector<int> ans(q);

    int elem_ptr = 0;
    for (int i = 0; i < q; i++) {
        while (elem_ptr < n && elements[elem_ptr].val > queries[i].k) {
            update(elements[elem_ptr].pos, 1);
            elem_ptr++;
        }
        ans[queries[i].id] = queryRange(queries[i].l, queries[i].r);
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
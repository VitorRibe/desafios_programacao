/*
I - Closest Equals

Dada uma sequência a_1, a_2, ..., a_n e m consultas l_j, r_j (1 <= l_j <= r_j <= n). Para cada consulta, você precisa imprimir a distância mínima entre um par de elementos a_x e a_y (x != y) tal que:
- ambos os índices dos elementos estão dentro do intervalo [l_j, r_j], isto é, l_j <= x, y <= r_j;
- os valores dos elementos são iguais, isto é, a_x = a_y.

O texto acima entende distância como |x - y|.

Entrada:
A primeira linha da entrada contém um par de inteiros n, m (1 <= n, m <= 5 * 10^5) — o comprimento da sequência e o número de consultas, respectivamente.
A segunda linha contém a sequência de inteiros a_1, a_2, ..., a_n (-10^9 <= a_i <= 10^9).
As próximas m linhas contêm as consultas, uma por linha. Cada consulta é dada por um par de números l_j, r_j (1 <= l_j <= r_j <= n) — os índices dos limites do intervalo da consulta.

Saída:
Imprima m inteiros — as respostas para cada consulta. Se não houver nenhum par válido para alguma consulta, imprima -1 como resposta para essa consulta.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct Query {
    int l, r, id;
    bool operator<(const Query& other) const {
        return r < other.r;
    }
};

int n, m;
vector<int> bit;

void update(int idx, int val) {
    for (; idx > 0; idx -= idx & -idx) {
        bit[idx] = min(bit[idx], val);
    }
}

int query(int idx) {
    int res = INF;
    for (; idx <= n; idx += idx & -idx) {
        res = min(res, bit[idx]);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    vector<int> a(n + 1);
    vector<int> vals;
    vals.reserve(n);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        vals.push_back(a[i]);
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    vector<Query> queries(m);
    for (int i = 0; i < m; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end());

    bit.assign(n + 1, INF);
    vector<int> last_pos(vals.size(), 0);
    vector<int> ans(m);

    int q_ptr = 0;
    for (int i = 1; i <= n; i++) {
        int comp_val = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();

        if (last_pos[comp_val] != 0) {
            int p = last_pos[comp_val];
            update(p, i - p);
        }
        last_pos[comp_val] = i;

        while (q_ptr < m && queries[q_ptr].r == i) {
            int res = query(queries[q_ptr].l);
            ans[queries[q_ptr].id] = (res == INF ? -1 : res);
            q_ptr++;
        }
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
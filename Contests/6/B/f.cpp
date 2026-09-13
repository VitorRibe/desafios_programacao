/*
F - Mais um Problema de Consultas de Array

Você recebe um array a de tamanho n, e q consultas do tipo:
- 1 l_i r_i: deslocamento cíclico do segmento à direita.
- 2 l_i r_i: reversão do segmento [l_i, r_i].

Existem m índices importantes no array b_1, b_2, ..., b_m. Para cada índice, você deve produzir o número que estará no índice b_i após todas as consultas.

Entrada:
A primeira linha contém três inteiros n, q e m (1 <= n, q <= 2*10^5, 1 <= m <= 100).
A segunda linha contém n inteiros a_1, a_2, ..., a_n.
As próximas q linhas contêm t_i, l_i, r_i, onde t_i é o tipo da consulta.
A última linha contém os índices importantes b_1, ..., b_m.

Saída:
Imprima m números após todas as consultas serem feitas.
*/

#include <iostream>
#include <vector>

using namespace std;

struct Query {
    int t, l, r;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, m;
    if (!(cin >> n >> q >> m)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].t >> queries[i].l >> queries[i].r;
    }

    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    for (int i = 0; i < m; i++) {
        int p = b[i];
        for (int j = q - 1; j >= 0; j--) {
            int t = queries[j].t;
            int l = queries[j].l;
            int r = queries[j].r;

            if (p >= l && p <= r) {
                if (t == 1) {
                    if (p == l) {
                        p = r;
                    } else {
                        p--;
                    }
                } else if (t == 2) {
                    p = l + r - p;
                }
            }
        }
        cout << a[p] << (i == m - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
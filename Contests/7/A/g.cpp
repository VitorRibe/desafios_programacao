/*
G - Mishka e Soma Interessante

A pequena Mishka gosta de programação. Como seu aniversário acabou de passar, seus amigos decidiram presenteá-la com um arranjo de inteiros não negativos a_1, a_2, ..., a_n de n elementos!

Mishka adorou o arranjo e decidiu instantaneamente determinar seu valor de beleza, mas ela é muito pequena e não consegue processar grandes arranjos. Justamente por isso, ela convidou você para visitá-la e pediu para que você processe m consultas.

Cada consulta é processada da seguinte forma:
1. Dois inteiros l e r (1 <= l <= r <= n) são especificados — os limites do segmento da consulta.
2. Os inteiros presentes no segmento do arranjo [l, r] (na sequência de inteiros a_l, a_{l+1}, ..., a_r) um número PAR de vezes são anotados.
3. A soma XOR dos inteiros anotados é calculada, e este valor é a resposta para a consulta. Formalmente, se os inteiros anotados no ponto 2 forem x_1, x_2, ..., x_k, então Mishka quer saber o valor x_1 ^ x_2 ^ ... ^ x_k, onde ^ representa o operador de OU exclusivo bit a bit (XOR).

Como apenas os pequenos ursos conhecem a definição de beleza do arranjo, tudo o que você precisa fazer é responder a cada uma das consultas apresentadas.

Entrada:
A primeira linha da entrada contém um único inteiro n (1 <= n <= 1 000 000) — o número de elementos no arranjo.
A segunda linha da entrada contém n inteiros a_1, a_2, ..., a_n (1 <= a_i <= 10^9) — os elementos do arranjo.
A terceira linha da entrada contém um único inteiro m (1 <= m <= 1 000 000) — o número de consultas.
Cada uma das próximas m linhas descreve a consulta correspondente por um par de inteiros l e r (1 <= l <= r <= n) — os limites do segmento da consulta.

Saída:
Imprima m inteiros não negativos — as respostas para as consultas na ordem em que aparecem na entrada.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Query {
    int l, r, id;
    bool operator<(const Query& other) const {
        return r < other.r;
    }
};

int n, m;
vector<int> a;
vector<int> pref_xor;
vector<int> bit;

void update(int idx, int val) {
    for (; idx <= n; idx += idx & -idx) {
        bit[idx] ^= val;
    }
}

int queryBIT(int idx) {
    int res = 0;
    for (; idx > 0; idx -= idx & -idx) {
        res ^= bit[idx];
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    a.resize(n + 1);
    pref_xor.resize(n + 1, 0);
    vector<int> vals;
    vals.reserve(n);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref_xor[i] = pref_xor[i - 1] ^ a[i];
        vals.push_back(a[i]);
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    cin >> m;
    vector<Query> queries(m);
    for (int i = 0; i < m; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end());

    bit.assign(n + 1, 0);
    vector<int> last_pos(vals.size(), 0);
    vector<int> ans(m);

    int q_ptr = 0;
    for (int i = 1; i <= n; i++) {
        int comp_val = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();

        if (last_pos[comp_val] != 0) {
            update(last_pos[comp_val], a[i]);
        }
        update(i, a[i]);
        last_pos[comp_val] = i;

        while (q_ptr < m && queries[q_ptr].r == i) {
            int l = queries[q_ptr].l;
            int r = queries[q_ptr].r;
            int distinct_xor = queryBIT(r) ^ queryBIT(l - 1);
            int range_pref_xor = pref_xor[r] ^ pref_xor[l - 1];
            ans[queries[q_ptr].id] = range_pref_xor ^ distinct_xor;
            q_ptr++;
        }
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
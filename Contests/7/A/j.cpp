/*
J - Uma Ocorrência

Você recebe um arranjo a consistindo de n inteiros e q consultas sobre ele. A i-ésima consulta é denotada por dois inteiros l_i e r_i. Para cada consulta, você deve encontrar qualquer inteiro que ocorra exatamente uma vez no subarranjo de a do índice l_i até o índice r_i (um subarranjo é um subsegmento contíguo de um arranjo). Por exemplo, se a = [1, 1, 2, 3, 2, 4], então para a consulta (l_i = 2, r_i = 6) o subarranjo de interesse é [1, 2, 3, 2, 4], e as respostas possíveis são 1, 3 e 4; para a consulta (l_i = 1, r_i = 2) o subarranjo de interesse é [1, 1], e não há nenhum elemento que ocorra exatamente uma vez.

Você consegue responder a todas as consultas?

Entrada:
A primeira linha contém um inteiro n (1 <= n <= 5 * 10^5).
A segunda linha contém n inteiros a_1, a_2, ..., a_n (1 <= a_i <= 5 * 10^5).
A terceira linha contém um inteiro q (1 <= q <= 5 * 10^5).
Em seguida, seguem q linhas, com a i-ésima linha contendo dois inteiros l_i e r_i representando a i-ésima consulta (1 <= l_i <= r_i <= n).

Saída:
Responda às consultas da seguinte forma:
Se não houver nenhum inteiro que ocorra no subarranjo do índice l_i ao índice r_i exatamente uma vez, imprima 0. Caso contrário, imprima qualquer um desses inteiros.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAXN = 500005;

struct Query {
    int l, r, id;
    bool operator<(const Query& other) const {
        return r < other.r;
    }
};

struct Node {
    int val, pos;
    bool operator<(const Node& other) const {
        return val < other.val;
    }
};

Node tree[4 * MAXN];
int a[MAXN];
int last_pos[MAXN];
int ans[MAXN];

void build(int node, int start, int end) {
    tree[node] = {INF, start};
    if (start == end) return;
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
}

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = {val, idx};
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update(2 * node, start, mid, idx, val);
    else update(2 * node + 1, mid + 1, end, idx, val);
    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return {INF, -1};
    if (l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    return min(query(2 * node, start, mid, l, r),
               query(2 * node + 1, mid + 1, end, l, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int q;
    cin >> q;

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end());

    build(1, 1, n);

    int q_ptr = 0;
    for (int i = 1; i <= n; i++) {
        if (last_pos[a[i]] != 0) {
            update(1, 1, n, last_pos[a[i]], INF);
        }
        update(1, 1, n, i, last_pos[a[i]]);
        last_pos[a[i]] = i;

        while (q_ptr < q && queries[q_ptr].r == i) {
            Node res = query(1, 1, n, queries[q_ptr].l, queries[q_ptr].r);
            if (res.val < queries[q_ptr].l) {
                ans[queries[q_ptr].id] = a[res.pos];
            } else {
                ans[queries[q_ptr].id] = 0;
            }
            q_ptr++;
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
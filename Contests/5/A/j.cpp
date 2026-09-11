/*
J - Consultas de Soma de Prefixo

Dado um array de n inteiros, sua tarefa é processar q consultas dos seguintes tipos:
1. atualizar o valor na posição k para u
2. qual é a soma de prefixo máxima no intervalo [a, b]?

Entrada:
A primeira linha de entrada tem dois inteiros n e q: o número de valores e consultas.
A segunda linha tem n inteiros x_1, x_2, ..., x_n: os valores do array.
Finalmente, existem q linhas descrevendo as consultas. Cada linha possui três inteiros: ou "1 k u" ou "2 a b".

Saída:
Imprima o resultado de cada consulta do tipo 2.

Restrições:
1 <= n, q <= 2 * 10^5
-10^9 <= x_i, u <= 10^9
1 <= k <= n
1 <= a <= b <= n
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    long long sum;
    long long pref;
};

vector<Node> tree;

Node merge(Node l, Node r) {
    Node res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    return res;
}

void build(const vector<long long>& a, int node, int start, int end) {
    if (start == end) {
        tree[node] = {a[start], max(0LL, a[start])};
        return;
    }
    int mid = (start + end) / 2;
    build(a, 2 * node, start, mid);
    build(a, 2 * node + 1, mid + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int start, int end, int idx, long long val) {
    if (start == end) {
        tree[node] = {val, max(0LL, val)};
        return;
    }
    int mid = (start + end) / 2;
    if (start <= idx && idx <= mid) {
        update(2 * node, start, mid, idx, val);
    } else {
        update(2 * node + 1, mid + 1, end, idx, val);
    }
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return {0, 0};
    if (l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    Node left = query(2 * node, start, mid, l, r);
    Node right = query(2 * node + 1, mid + 1, end, l, r);
    if (r <= mid) return left;
    if (l > mid) return right;
    return merge(left, right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    tree.resize(4 * n);
    build(a, 1, 0, n - 1);
    
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            long long u;
            cin >> k >> u;
            update(1, 0, n - 1, k - 1, u);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(1, 0, n - 1, l - 1, r - 1).pref << "\n";
        }
    }
    
    return 0;
}
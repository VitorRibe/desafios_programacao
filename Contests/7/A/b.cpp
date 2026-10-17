/*
B - Múltiplos de 3

Existem N números a[0], a[1] ... a[N - 1]. Inicialmente todos são 0. Você precisa realizar dois tipos de operações:

1. Aumentar em 1 os números entre os índices A e B (inclusive). Isso é representado pelo comando "0 A B".
2. Responder quantos números entre os índices A e B (inclusive) são divisíveis por 3. Isso é representado pelo comando "1 A B".

Entrada:
A primeira linha contém dois inteiros, N e Q. Cada uma das próximas Q linhas é da forma "0 A B" ou "1 A B", conforme mencionado acima.

Saída:
Imprima 1 linha para cada uma das consultas da forma "1 A B" contendo a resposta necessária para a consulta correspondente.

Restrições:
1 <= N <= 100000
1 <= Q <= 100000
0 <= A <= B <= N - 1
*/

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int cnt[3];
};

const int MAXN = 100005;
Node tree[4 * MAXN];
int lazy[4 * MAXN];

void build(int node, int start, int end) {
    lazy[node] = 0;
    if (start == end) {
        tree[node].cnt[0] = 1;
        tree[node].cnt[1] = 0;
        tree[node].cnt[2] = 0;
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node].cnt[0] = tree[2 * node].cnt[0] + tree[2 * node + 1].cnt[0];
    tree[node].cnt[1] = tree[2 * node].cnt[1] + tree[2 * node + 1].cnt[1];
    tree[node].cnt[2] = tree[2 * node].cnt[2] + tree[2 * node + 1].cnt[2];
}

void shift(int node) {
    int c0 = tree[node].cnt[0];
    int c1 = tree[node].cnt[1];
    int c2 = tree[node].cnt[2];
    tree[node].cnt[0] = c2;
    tree[node].cnt[1] = c0;
    tree[node].cnt[2] = c1;
}

void push(int node, int start, int end) {
    if (lazy[node] != 0) {
        int times = lazy[node] % 3;
        for (int i = 0; i < times; i++) {
            shift(node);
        }
        if (start != end) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int l, int r) {
    push(node, start, end);
    if (start > r || end < l) return;
    if (start >= l && end <= r) {
        lazy[node]++;
        push(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r);
    update(2 * node + 1, mid + 1, end, l, r);
    tree[node].cnt[0] = tree[2 * node].cnt[0] + tree[2 * node + 1].cnt[0];
    tree[node].cnt[1] = tree[2 * node].cnt[1] + tree[2 * node + 1].cnt[1];
    tree[node].cnt[2] = tree[2 * node].cnt[2] + tree[2 * node + 1].cnt[2];
}

int query(int node, int start, int end, int l, int r) {
    push(node, start, end);
    if (start > r || end < l) return 0;
    if (start >= l && end <= r) {
        return tree[node].cnt[0];
    }
    int mid = (start + end) / 2;
    int p1 = query(2 * node, start, mid, l, r);
    int p2 = query(2 * node + 1, mid + 1, end, l, r);
    return p1 + p2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    build(1, 0, n - 1);

    while (q--) {
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 0) {
            update(1, 0, n - 1, a, b);
        } else {
            cout << query(1, 0, n - 1, a, b) << "\n";
        }
    }

    return 0;
}
/*
F - Consultas de Soma de Subarranjo

Existe um array consistindo de n inteiros. Alguns valores do array serão atualizados, e após cada atualização, sua tarefa é relatar a soma máxima de subarranjo no array.

Entrada:
A primeira linha de entrada contém os inteiros n e m: o tamanho do array e o número de atualizações. O array é indexado 1, 2, ..., n.
A próxima linha tem n inteiros: x_1, x_2, ..., x_n: o conteúdo inicial do array.
Então existem m linhas descrevendo as mudanças. Cada linha tem dois inteiros k e x: o valor na posição k torna-se x.

Saída:
Após cada atualização, imprima a soma máxima do subarranjo. Subarranjos vazios (com soma 0) são permitidos.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

struct Node {
    int sum, pref, suff, ans;
};

const int MAXN = 200005;
Node st[4 * MAXN];
int arr[MAXN];

Node merge(Node l, Node r) {
    Node res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max({l.ans, r.ans, l.suff + r.pref});
    return res;
}

void apply(int node, int v) {
    st[node].sum = v;
    st[node].pref = max(0LL, v);
    st[node].suff = max(0LL, v);
    st[node].ans = max(0LL, v);
}

void build(int node, int l, int r) {
    if (l == r) {
        apply(node, arr[l]);
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    st[node] = merge(st[2 * node], st[2 * node + 1]);
}

void update(int node, int l, int r, int k, int x) {
    if (l == r) {
        apply(node, x);
        return;
    }
    int mid = l + (r - l) / 2;
    if (k <= mid) update(2 * node, l, mid, k, x);
    else update(2 * node + 1, mid + 1, r, k, x);
    st[node] = merge(st[2 * node], st[2 * node + 1]);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(1, 1, n);
    while (m--) {
        int k, x;
        cin >> k >> x;
        update(1, 1, n, k, x);
        cout << st[1].ans << "\n";
    }
    return 0;
}
/*
H - RMQ Circular

Você recebe um array circular a_0, a_1, ..., a_{n-1}. Existem dois tipos de operações:
- inc(lf, rg, v) — aumenta cada elemento no segmento [lf, rg] (inclusivamente) em v;
- rmq(lf, rg) — retorna o valor mínimo no segmento [lf, rg] (inclusivamente).
Assuma que os segmentos são circulares, então se n=5 e lf=3, rg=1, significa a sequência de índices: 3, 4, 0, 1.

Entrada:
A primeira linha contém o inteiro n. A próxima linha contém o estado inicial do array. A terceira linha contém o inteiro m — o número de operações. As próximas m linhas contêm as operações. Duas variáveis indicam rmq, três variáveis indicam inc.

Saída:
Para cada operação rmq, escreva o resultado.
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

#define int long long

const int INF = 1e18;
const int MAXN = 200005;
int st[4 * MAXN], lz[4 * MAXN];
int a[MAXN];

void apply(int node, int v) {
    st[node] += v;
    lz[node] += v;
}

void push(int node) {
    if (lz[node] != 0) {
        apply(2 * node, lz[node]);
        apply(2 * node + 1, lz[node]);
        lz[node] = 0;
    }
}

void build(int node, int l, int r) {
    if (l == r) {
        st[node] = a[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    st[node] = min(st[2 * node], st[2 * node + 1]);
}

void update(int node, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        apply(node, v);
        return;
    }
    push(node);
    int mid = l + (r - l) / 2;
    if (ql <= mid) update(2 * node, l, mid, ql, qr, v);
    if (qr > mid) update(2 * node + 1, mid + 1, r, ql, qr, v);
    st[node] = min(st[2 * node], st[2 * node + 1]);
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return st[node];
    push(node);
    int mid = l + (r - l) / 2;
    int res = INF;
    if (ql <= mid) res = min(res, query(2 * node, l, mid, ql, qr));
    if (qr > mid) res = min(res, query(2 * node + 1, mid + 1, r, ql, qr));
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    for (int i = 0; i < n; i++) cin >> a[i];
    build(1, 0, n - 1);
    int m;
    cin >> m;
    string line;
    getline(cin, line);
    while (m--) {
        getline(cin, line);
        stringstream ss(line);
        vector<int> q;
        int x;
        while (ss >> x) q.push_back(x);
        if (q.size() == 3) {
            int lf = q[0], rg = q[1], v = q[2];
            if (lf <= rg) update(1, 0, n - 1, lf, rg, v);
            else {
                update(1, 0, n - 1, lf, n - 1, v);
                update(1, 0, n - 1, 0, rg, v);
            }
        } else {
            int lf = q[0], rg = q[1];
            if (lf <= rg) cout << query(1, 0, n - 1, lf, rg) << "\n";
            else cout << min(query(1, 0, n - 1, lf, n - 1), query(1, 0, n - 1, 0, rg)) << "\n";
        }
    }
    return 0;
}
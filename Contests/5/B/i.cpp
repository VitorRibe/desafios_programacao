/*
I - Soma de Intervalo Afim

Você recebe um array a_0, a_1, ..., a_{N-1}. Processe Q consultas dos seguintes tipos:
- 0 l r b c: Para cada i = l, l+1, ..., r-1, defina a_i = b * a_i + c.
- 1 l r: Imprima a soma a_l + ... + a_{r-1} mod 998244353.

Entrada:
A entrada é dada no seguinte formato:
N Q
a_0 a_1 ... a_{N-1}
Query_0
...
Query_{Q-1}

Saída:
Para cada consulta do segundo tipo, imprima a resposta.
*/
#include <iostream>
#include <vector>

using namespace std;

#define int long long

const int MOD = 998244353;
const int MAXN = 500005;
int st[4 * MAXN], lz_b[4 * MAXN], lz_c[4 * MAXN];
int a[MAXN];

void apply(int node, int len, int b, int c) {
    st[node] = (st[node] * b + c * len) % MOD;
    lz_b[node] = (lz_b[node] * b) % MOD;
    lz_c[node] = (lz_c[node] * b + c) % MOD;
}

void push(int node, int l, int r) {
    if (lz_b[node] != 1 || lz_c[node] != 0) {
        int mid = l + (r - l) / 2;
        int len_left = mid - l + 1;
        int len_right = r - mid;
        apply(2 * node, len_left, lz_b[node], lz_c[node]);
        apply(2 * node + 1, len_right, lz_b[node], lz_c[node]);
        lz_b[node] = 1;
        lz_c[node] = 0;
    }
}

void build(int node, int l, int r) {
    lz_b[node] = 1;
    lz_c[node] = 0;
    if (l == r) {
        st[node] = a[l] % MOD;
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    st[node] = (st[2 * node] + st[2 * node + 1]) % MOD;
}

void update(int node, int l, int r, int ql, int qr, int b, int c) {
    if (ql <= l && r <= qr) {
        apply(node, r - l + 1, b, c);
        return;
    }
    push(node, l, r);
    int mid = l + (r - l) / 2;
    if (ql <= mid) update(2 * node, l, mid, ql, qr, b, c);
    if (qr > mid) update(2 * node + 1, mid + 1, r, ql, qr, b, c);
    st[node] = (st[2 * node] + st[2 * node + 1]) % MOD;
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return st[node];
    push(node, l, r);
    int mid = l + (r - l) / 2;
    int res = 0;
    if (ql <= mid) res = (res + query(2 * node, l, mid, ql, qr)) % MOD;
    if (qr > mid) res = (res + query(2 * node + 1, mid + 1, r, ql, qr)) % MOD;
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    for (int i = 0; i < n; i++) cin >> a[i];
    if (n > 0) build(1, 0, n - 1);
    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        r--;
        if (type == 0) {
            int b, c;
            cin >> b >> c;
            if (l <= r) update(1, 0, n - 1, l, r, b, c);
        } else {
            if (l <= r) cout << query(1, 0, n - 1, l, r) << "\n";
            else cout << 0 << "\n";
        }
    }
    return 0;
}
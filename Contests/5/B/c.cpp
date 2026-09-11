/*
C - Atualizações e Somas de Intervalo

Sua tarefa é manter um array de n valores e processar eficientemente os seguintes tipos de consultas:
1. Aumentar cada valor no intervalo [a, b] em x.
2. Definir cada valor no intervalo [a, b] como x.
3. Calcular a soma dos valores no intervalo [a, b].

Entrada:
A primeira linha de entrada tem dois inteiros n e q: o tamanho do array e o número de consultas.
A próxima linha tem n valores t_1, t_2, ..., t_n: os conteúdos iniciais do array.
Finalmente, existem q linhas descrevendo as consultas. O formato de cada linha é um dos seguintes: "1 a b x", "2 a b x", ou "3 a b".

Saída:
Imprima a resposta para cada consulta de soma.
*/
#include <iostream>
#include <vector>

using namespace std;

#define int long long

const int MAXN = 200005;
int st[4 * MAXN], lz_add[4 * MAXN], lz_set[4 * MAXN];
bool has_set[4 * MAXN];
int a[MAXN];

void apply_set(int node, int l, int r, int v) {
    st[node] = (r - l + 1) * v;
    lz_set[node] = v;
    has_set[node] = true;
    lz_add[node] = 0;
}

void apply_add(int node, int l, int r, int v) {
    st[node] += (r - l + 1) * v;
    lz_add[node] += v;
}

void push(int node, int l, int r) {
    int mid = l + (r - l) / 2;
    if (has_set[node]) {
        apply_set(2 * node, l, mid, lz_set[node]);
        apply_set(2 * node + 1, mid + 1, r, lz_set[node]);
        has_set[node] = false;
    }
    if (lz_add[node] != 0) {
        apply_add(2 * node, l, mid, lz_add[node]);
        apply_add(2 * node + 1, mid + 1, r, lz_add[node]);
        lz_add[node] = 0;
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
    st[node] = st[2 * node] + st[2 * node + 1];
}

void update_add(int node, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        apply_add(node, l, r, v);
        return;
    }
    push(node, l, r);
    int mid = l + (r - l) / 2;
    if (ql <= mid) update_add(2 * node, l, mid, ql, qr, v);
    if (qr > mid) update_add(2 * node + 1, mid + 1, r, ql, qr, v);
    st[node] = st[2 * node] + st[2 * node + 1];
}

void update_set(int node, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        apply_set(node, l, r, v);
        return;
    }
    push(node, l, r);
    int mid = l + (r - l) / 2;
    if (ql <= mid) update_set(2 * node, l, mid, ql, qr, v);
    if (qr > mid) update_set(2 * node + 1, mid + 1, r, ql, qr, v);
    st[node] = st[2 * node] + st[2 * node + 1];
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return st[node];
    push(node, l, r);
    int mid = l + (r - l) / 2;
    int res = 0;
    if (ql <= mid) res += query(2 * node, l, mid, ql, qr);
    if (qr > mid) res += query(2 * node + 1, mid + 1, r, ql, qr);
    return res;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) {
            int x; cin >> x;
            update_add(1, 1, n, l, r, x);
        } else if (type == 2) {
            int x; cin >> x;
            update_set(1, 1, n, l, r, x);
        } else {
            cout << query(1, 1, n, l, r) << "\n";
        }
    }
    return 0;
}
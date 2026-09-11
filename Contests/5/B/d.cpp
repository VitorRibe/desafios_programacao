/*
D - Consultas Polinomiais

Sua tarefa é manter um array de n valores e processar eficientemente os seguintes tipos de consultas:
1. Aumentar o primeiro valor no intervalo [a, b] em 1, o segundo valor em 2, o terceiro valor em 3, e assim por diante.
2. Calcular a soma dos valores no intervalo [a, b].

Entrada:
A primeira linha de entrada tem dois inteiros n e q: o tamanho do array e o número de consultas.
A próxima linha tem n valores t_1, t_2, ..., t_n: os conteúdos iniciais do array.
Finalmente, existem q linhas descrevendo as consultas. O formato de cada linha é "1 a b" ou "2 a b".

Saída:
Imprima a resposta para cada consulta de soma.
*/
#include <iostream>
#include <vector>

using namespace std;

#define int long long

const int MAXN = 200005;
int st[4 * MAXN], lz_a[4 * MAXN], lz_d[4 * MAXN];
int arr[MAXN];

void apply(int node, int len, int a, int d) {
    st[node] += a * len + d * len * (len - 1) / 2;
    lz_a[node] += a;
    lz_d[node] += d;
}

void push(int node, int l, int r) {
    if (lz_a[node] != 0 || lz_d[node] != 0) {
        int mid = l + (r - l) / 2;
        int len_left = mid - l + 1;
        int len_right = r - mid;
        apply(2 * node, len_left, lz_a[node], lz_d[node]);
        apply(2 * node + 1, len_right, lz_a[node] + lz_d[node] * len_left, lz_d[node]);
        lz_a[node] = lz_d[node] = 0;
    }
}

void build(int node, int l, int r) {
    if (l == r) {
        st[node] = arr[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    st[node] = st[2 * node] + st[2 * node + 1];
}

void update(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        apply(node, r - l + 1, l - ql + 1, 1);
        return;
    }
    push(node, l, r);
    int mid = l + (r - l) / 2;
    if (ql <= mid) update(2 * node, l, mid, ql, qr);
    if (qr > mid) update(2 * node + 1, mid + 1, r, ql, qr);
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
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(1, 1, n);
    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        if (type == 1) update(1, 1, n, l, r);
        else cout << query(1, 1, n, l, r) << "\n";
    }
    return 0;
}
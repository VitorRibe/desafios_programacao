/*
G - Consultas Horríveis

O mundo está ficando mais maligno e está cada vez mais difícil entrar na Liga do Mal. Como o lendário Bad Horse se aposentou, agora você precisa responder corretamente às perguntas malignas do Dr. Horrible. Você recebe um array de N elementos, inicialmente todos 0. Depois disso, receberá C comandos:
- 0 p q v: adicionar v a todos os números no intervalo de p a q (inclusivo).
- 1 p q: imprimir uma linha contendo a soma de todos os elementos do array entre p e q (inclusivo).

Entrada:
A primeira linha conterá T, o número de casos de teste.
Cada caso de teste começará com N e C. Depois disso, você receberá C comandos no formato mencionado.

Saída:
Imprima as respostas das consultas.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

void solve() {
    int n, c;
    cin >> n >> c;
    vector<int> st(4 * n + 1, 0), lz(4 * n + 1, 0);

    auto apply = [&](int node, int l, int r, int v) {
        st[node] += (r - l + 1) * v;
        lz[node] += v;
    };

    auto push = [&](int node, int l, int r) {
        if (lz[node] != 0) {
            int mid = l + (r - l) / 2;
            apply(2 * node, l, mid, lz[node]);
            apply(2 * node + 1, mid + 1, r, lz[node]);
            lz[node] = 0;
        }
    };

    auto update = [&](auto self, int node, int l, int r, int ql, int qr, int v) -> void {
        if (ql <= l && r <= qr) {
            apply(node, l, r, v);
            return;
        }
        push(node, l, r);
        int mid = l + (r - l) / 2;
        if (ql <= mid) self(self, 2 * node, l, mid, ql, qr, v);
        if (qr > mid) self(self, 2 * node + 1, mid + 1, r, ql, qr, v);
        st[node] = st[2 * node] + st[2 * node + 1];
    };

    auto query = [&](auto self, int node, int l, int r, int ql, int qr) -> int {
        if (ql <= l && r <= qr) return st[node];
        push(node, l, r);
        int mid = l + (r - l) / 2;
        int res = 0;
        if (ql <= mid) res += self(self, 2 * node, l, mid, ql, qr);
        if (qr > mid) res += self(self, 2 * node + 1, mid + 1, r, ql, qr);
        return res;
    };

    while (c--) {
        int type, p, q;
        cin >> type >> p >> q;
        if (p > q) swap(p, q);
        if (type == 0) {
            int v;
            cin >> v;
            update(update, 1, 1, n, p, q, v);
        } else {
            cout << query(query, 1, 1, n, p, q) << "\n";
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
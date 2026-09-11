/*
A - Consultas de Hotel

Existem n hotéis em uma rua. Para cada hotel você sabe o número de quartos livres. Sua tarefa é atribuir quartos de hotel para grupos de turistas. Todos os membros de um grupo querem ficar no mesmo hotel.

Os grupos virão a você um após o outro, e você sabe para cada grupo o número de quartos que ele necessita. Você sempre atribui um grupo ao primeiro hotel que tem quartos suficientes. Após isso, o número de quartos livres no hotel diminui.

Entrada:
A primeira linha de entrada contém dois inteiros n e m: o número de hotéis e o número de grupos. Os hotéis são numerados de 1, 2, ..., n.
A próxima linha contém n inteiros h_1, h_2, ..., h_n: o número de quartos livres em cada hotel.
A última linha contém m inteiros r_1, r_2, ..., r_m: o número de quartos que cada grupo requer.

Saída:
Imprima o hotel atribuído para cada grupo. Se um grupo não puder ser atribuído a um hotel, imprima 0 em vez disso.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
long long st[4 * MAXN], a[MAXN];

void build(int node, int l, int r) {
    if (l == r) {
        st[node] = a[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    st[node] = max(st[2 * node], st[2 * node + 1]);
}

void query(int node, int l, int r, long long x) {
    if (st[node] < x) {
        cout << 0 << " ";
        return;
    }
    if (l == r) {
        cout << l << " ";
        st[node] -= x;
        return;
    }
    int mid = l + (r - l) / 2;
    if (st[2 * node] >= x) {
        query(2 * node, l, mid, x);
    } else {
        query(2 * node + 1, mid + 1, r, x);
    }
    st[node] = max(st[2 * node], st[2 * node + 1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        long long r_req;
        cin >> r_req;
        query(1, 1, n, r_req);
    }
    cout << "\n";
    return 0;
}
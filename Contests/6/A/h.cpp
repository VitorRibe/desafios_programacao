/*
H - Multiconjunto (Multiset)

Você recebe um multiconjunto consistindo de n inteiros. Você tem que processar consultas de dois tipos:
- adicionar o inteiro k ao multiconjunto;
- encontrar a k-ésima estatística de ordem no multiconjunto e removê-la.
Após processar todas as consultas, imprima qualquer número pertencente ao multiconjunto, ou diga que ele está vazio (0).

Entrada:
A primeira linha contém dois inteiros n e q.
A segunda linha contém n inteiros a_1, a_2, ..., a_n — os elementos do multiconjunto.
A terceira linha contém q inteiros k_1, k_2, ..., k_q:
- se 1 <= k_i <= n, insira k_i no multiconjunto.
- se k_i < 0, remova a |k_i|-ésima estatística de ordem do multiconjunto.
*/

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000005;
int bit[MAXN];

void add(int i, int delta) {
    for (; i < MAXN; i += i & -i) {
        bit[i] += delta;
    }
}

int find_kth(int k) {
    int pos = 0;
    for (int i = 20; i >= 0; i--) {
        if (pos + (1 << i) < MAXN && bit[pos + (1 << i)] < k) {
            pos += (1 << i);
            k -= bit[pos];
        }
    }
    return pos + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    int total_elements = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        add(x, 1);
        total_elements++;
    }

    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        if (k > 0) {
            add(k, 1);
            total_elements++;
        } else {
            k = -k;
            int pos = find_kth(k);
            add(pos, -1);
            total_elements--;
        }
    }

    if (total_elements == 0) {
        cout << 0 << "\n";
    } else {
        cout << find_kth(1) << "\n";
    }

    return 0;
}
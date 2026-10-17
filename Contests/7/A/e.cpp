/*
E - Give Away

É dado um arranjo X (indexado em 1), consistindo de N inteiros, e um conjunto de Q consultas. Existem dois tipos de consultas:

1. 0 a b c
   Aqui você deve retornar o número de elementos com índices em [a, b] maiores ou iguais a c.
2. 1 a b
   Aqui você deve alterar o a-ésimo elemento do arranjo para b.

Entrada:
A primeira linha contém N, o número de elementos no arranjo X. A próxima linha contém N inteiros separados por espaço representando os elementos de X. A terceira linha da entrada contém um único inteiro, Q, o número de consultas. As próximas Q linhas contêm consultas de dois tipos, conforme descrito acima.

Saída:
Linhas contendo a resposta para cada consulta do tipo 0.

Restrições:
1 <= N <= 5 * 10^5
1 <= Q <= 10^5
1 <= X[i] <= 10^9
1 <= a <= b <= N para consultas do tipo 0
1 <= a <= N, 1 <= b <= 10^9 para consultas do tipo 1
1 <= c <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 500005;
const int BLK = 1000;

int n, q;
int a[MAXN];
vector<int> b[MAXN / BLK + 5];

void update(int idx, int val) {
    int block_idx = idx / BLK;
    int old_val = a[idx];
    a[idx] = val;

    auto it = lower_bound(b[block_idx].begin(), b[block_idx].end(), old_val);
    if (it != b[block_idx].end()) {
        *it = val;
        sort(b[block_idx].begin(), b[block_idx].end());
    }
}

int query(int l, int r, int c) {
    int left_block = l / BLK;
    int right_block = r / BLK;
    int count = 0;

    if (left_block == right_block) {
        for (int i = l; i <= r; i++) {
            if (a[i] >= c) {
                count++;
            }
        }
    } else {
        int end_left = (left_block + 1) * BLK - 1;
        for (int i = l; i <= end_left; i++) {
            if (a[i] >= c) {
                count++;
            }
        }

        for (int i = left_block + 1; i < right_block; i++) {
            auto it = lower_bound(b[i].begin(), b[i].end(), c);
            count += (b[i].end() - it);
        }

        int start_right = right_block * BLK;
        for (int i = start_right; i <= r; i++) {
            if (a[i] >= c) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i / BLK].push_back(a[i]);
    }

    int num_blocks = n / BLK + 1;
    for (int i = 0; i < num_blocks; i++) {
        sort(b[i].begin(), b[i].end());
    }

    cin >> q;

    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int l, r, c;
            cin >> l >> r >> c;
            cout << query(l, r, c) << "\n";
        } else {
            int idx, val;
            cin >> idx >> val;
            update(idx, val);
        }
    }

    return 0;
}
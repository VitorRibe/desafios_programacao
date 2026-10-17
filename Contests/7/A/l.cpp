/*
L - GukiZ e GukiZiana

O Professor GukiZ estava brincando com arranjos novamente e acidentalmente descobriu uma nova função, a qual ele chamou de GukiZiana. Para um determinado arranjo a, indexado com inteiros de 1 a n, e um número y, GukiZiana(a, y) representa o valor máximo de j - i, tal que a_j = a_i = y. Se não houver nenhum y como elemento em a, então GukiZiana(a, y) é igual a -1. GukiZ também preparou um problema para você. Desta vez, você tem dois tipos de consultas:

1. O primeiro tipo tem a forma 1 l r x e pede para você aumentar os valores de todos os a_i tais que l <= i <= r pelo inteiro não negativo x.
2. O segundo tipo tem a forma 2 y e pede para você encontrar o valor de GukiZiana(a, y).

Para cada consulta do tipo 2, imprima a resposta e faça o GukiZ feliz!

Entrada:
A primeira linha contém dois inteiros n, q (1 <= n <= 5 * 10^5, 1 <= q <= 5 * 10^4), o tamanho do arranjo a e o número de consultas.
A segunda linha contém n inteiros a_1, a_2, ..., a_n (1 <= a_i <= 10^9), formando o arranjo a.
Cada uma das próximas q linhas contém quatro ou dois números, conforme descrito no enunciado:
Se a linha começar com 1, então a consulta é da forma 1 l r x (1 <= l <= r <= n, 0 <= x <= 10^9), consulta do primeiro tipo.
Se a linha começar com 2, então a consulta é da forma 2 y (1 <= y <= 10^9), consulta do segundo tipo.

Saída:
Para cada consulta do tipo 2, imprima o valor de GukiZiana(a, y) para o valor de y daquela consulta.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 500005;
const int BLK = 700;

struct Element {
    long long val;
    int id;

    bool operator<(const Element& other) const {
        return val < other.val;
    }
};

int n, q;
long long a[MAXN];
long long lazy[MAXN / BLK + 5];
vector<Element> blocks[MAXN / BLK + 5];

void rebuild(int b) {
    int start = b * BLK + 1;
    int end = min(n, (b + 1) * BLK);
    blocks[b].clear();
    for (int i = start; i <= end; i++) {
        blocks[b].push_back({a[i], i});
    }
    sort(blocks[b].begin(), blocks[b].end());
}

void update(int l, int r, long long x) {
    int b_l = (l - 1) / BLK;
    int b_r = (r - 1) / BLK;

    if (b_l == b_r) {
        for (int i = l; i <= r; i++) {
            a[i] += x;
        }
        rebuild(b_l);
    } else {
        int end_l = (b_l + 1) * BLK;
        for (int i = l; i <= end_l; i++) {
            a[i] += x;
        }
        rebuild(b_l);

        for (int b = b_l + 1; b < b_r; b++) {
            lazy[b] += x;
        }

        int start_r = b_r * BLK + 1;
        for (int i = start_r; i <= r; i++) {
            a[i] += x;
        }
        rebuild(b_r);
    }
}

int query(long long y) {
    int min_idx = -1;
    int max_idx = -1;
    int num_blocks = (n + BLK - 1) / BLK;

    for (int b = 0; b < num_blocks; b++) {
        long long target = y - lazy[b];
        auto it = lower_bound(blocks[b].begin(), blocks[b].end(), Element{target, 0});
        if (it != blocks[b].end() && it->val == target) {
            int start = b * BLK + 1;
            int end = min(n, (b + 1) * BLK);
            for (int i = start; i <= end; i++) {
                if (a[i] + lazy[b] == y) {
                    min_idx = i;
                    break;
                }
            }
            break;
        }
    }

    if (min_idx == -1) return -1;

    for (int b = num_blocks - 1; b >= 0; b--) {
        long long target = y - lazy[b];
        auto it = lower_bound(blocks[b].begin(), blocks[b].end(), Element{target, 0});
        if (it != blocks[b].end() && it->val == target) {
            int start = b * BLK + 1;
            int end = min(n, (b + 1) * BLK);
            for (int i = end; i >= start; i--) {
                if (a[i] + lazy[b] == y) {
                    max_idx = i;
                    break;
                }
            }
            break;
        }
    }

    return max_idx - min_idx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int num_blocks = (n + BLK - 1) / BLK;
    for (int b = 0; b < num_blocks; b++) {
        rebuild(b);
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            update(l, r, x);
        } else {
            long long y;
            cin >> y;
            cout << query(y) << "\n";
        }
    }

    return 0;
}
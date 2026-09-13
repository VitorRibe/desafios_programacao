/*
A - Problema do Antecessor

Seja S um conjunto de inteiros entre 0 e N - 1. Processe as seguintes Q consultas:
0 k: Se k não pertence a S, insira k em S. Se k pertence a S, não faça nada.
1 k: Se k pertence a S, remova k de S. Se k não pertence a S, não faça nada.
2 k: Se S contém k, imprima 1. Caso contrário, imprima 0.
3 k: Imprima a menor chave que seja maior ou igual a k (se não houver, imprima -1).
4 k: Imprima a maior chave que seja menor ou igual a k (se não houver, imprima -1).

Restrições:
1 <= N <= 10^7
1 <= Q <= 10^6
0 <= k_i < N

Entrada:
O estado inicial de S é dado como uma string T de comprimento N consistindo de 0 e 1. S contém i se e somente se T_i = 1.
A primeira linha contém N e Q. Em seguida a string T, seguida por Q linhas com c_i e k_i.
*/

#include <iostream>
#include <string>
#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>
inline int get_lsb(uint64_t x) {
    unsigned long idx;
    _BitScanForward64(&idx, x);
    return (int)idx;
}
inline int get_msb(uint64_t x) {
    unsigned long idx;
    _BitScanReverse64(&idx, x);
    return (int)idx;
}
#else
inline int get_lsb(uint64_t x) {
    return __builtin_ctzll(x);
}
inline int get_msb(uint64_t x) {
    return 63 - __builtin_clzll(x);
}
#endif

using namespace std;

const int MAXN = 10000000;
uint64_t L0[MAXN / 64 + 2];
uint64_t L1[MAXN / 4096 + 2];
uint64_t L2[MAXN / 262144 + 2];
int n, q;

void insert_val(int k) {
    L0[k / 64] |= (1ULL << (k % 64));
    L1[k / 4096] |= (1ULL << ((k / 64) % 64));
    L2[k / 262144] |= (1ULL << ((k / 4096) % 64));
}

void erase_val(int k) {
    L0[k / 64] &= ~(1ULL << (k % 64));
    if (!L0[k / 64]) {
        L1[k / 4096] &= ~(1ULL << ((k / 64) % 64));
        if (!L1[k / 4096]) {
            L2[k / 262144] &= ~(1ULL << ((k / 4096) % 64));
        }
    }
}

int contains_val(int k) {
    return (L0[k / 64] >> (k % 64)) & 1;
}

int succ(int k) {
    if (k >= n) return -1;
    int b0 = k / 64;
    uint64_t m0 = L0[b0] & (~0ULL << (k % 64));
    if (m0) return b0 * 64 + get_lsb(m0);

    int b1 = b0 / 64;
    uint64_t m1 = 0;
    if (b0 % 64 != 63) m1 = L1[b1] & (~0ULL << ((b0 % 64) + 1));
    if (m1) {
        int nb0 = b1 * 64 + get_lsb(m1);
        return nb0 * 64 + get_lsb(L0[nb0]);
    }

    int b2 = b1 / 64;
    uint64_t m2 = 0;
    if (b1 % 64 != 63) m2 = L2[b2] & (~0ULL << ((b1 % 64) + 1));
    if (m2) {
        int nb1 = b2 * 64 + get_lsb(m2);
        int nb0 = nb1 * 64 + get_lsb(L1[nb1]);
        return nb0 * 64 + get_lsb(L0[nb0]);
    }

    for (int i = b2 + 1; i <= n / 262144; i++) {
        if (L2[i]) {
            int nb1 = i * 64 + get_lsb(L2[i]);
            int nb0 = nb1 * 64 + get_lsb(L1[nb1]);
            return nb0 * 64 + get_lsb(L0[nb0]);
        }
    }
    return -1;
}

int pred(int k) {
    if (k < 0) return -1;
    if (k >= n) k = n - 1;
    int b0 = k / 64;
    uint64_t m0 = L0[b0];
    if (k % 64 != 63) m0 &= (1ULL << ((k % 64) + 1)) - 1;
    if (m0) return b0 * 64 + get_msb(m0);

    int b1 = b0 / 64;
    uint64_t m1 = L1[b1];
    if (b0 % 64 != 0) {
        m1 &= (1ULL << (b0 % 64)) - 1;
        if (m1) {
            int nb0 = b1 * 64 + get_msb(m1);
            return nb0 * 64 + get_msb(L0[nb0]);
        }
    }

    int b2 = b1 / 64;
    uint64_t m2 = L2[b2];
    if (b1 % 64 != 0) {
        m2 &= (1ULL << (b1 % 64)) - 1;
        if (m2) {
            int nb1 = b2 * 64 + get_msb(m2);
            int nb0 = nb1 * 64 + get_msb(L1[nb1]);
            return nb0 * 64 + get_msb(L0[nb0]);
        }
    }

    for (int i = b2 - 1; i >= 0; i--) {
        if (L2[i]) {
            int nb1 = i * 64 + get_msb(L2[i]);
            int nb0 = nb1 * 64 + get_msb(L1[nb1]);
            return nb0 * 64 + get_msb(L0[nb0]);
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> q)) return 0;

    string t;
    cin >> t;
    for (int i = 0; i < n; i++) {
        if (t[i] == '1') {
            insert_val(i);
        }
    }

    while (q--) {
        int c, k;
        cin >> c >> k;
        if (c == 0) {
            insert_val(k);
        } else if (c == 1) {
            erase_val(k);
        } else if (c == 2) {
            cout << contains_val(k) << "\n";
        } else if (c == 3) {
            cout << succ(k) << "\n";
        } else if (c == 4) {
            cout << pred(k) << "\n";
        }
    }

    return 0;
}
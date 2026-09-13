/*
I - RMQ Estático

Você recebe uma sequência de inteiros a_0, a_1, ..., a_{N-1} com o comprimento N.
Processe Q consultas em ordem:
- l_i r_i: Imprima a min(a_{l_i}, a_{l_i+1}, ..., a_{r_i-1}).

Restrições:
1 <= N, Q <= 5 * 10^5
0 <= a_i <= 10^9
0 <= l_i < r_i <= N
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 500005;
const int LOGN = 20;

int st[LOGN][MAXN];
int lg[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    for (int i = 0; i < n; i++) {
        cin >> st[0][i];
    }

    lg[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i / 2] + 1;
    }

    for (int i = 1; i <= lg[n]; i++) {
        for (int j = 0; j + (1 << i) <= n; j++) {
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        int len = r - l;
        int k = lg[len];
        cout << min(st[k][l], st[k][r - (1 << k)]) << "\n";
    }

    return 0;
}
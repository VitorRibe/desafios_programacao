/*
C - Consultas de Mínimo de Intervalo Dinâmico

Dado um array de n inteiros, sua tarefa é processar q consultas dos seguintes tipos:
1. atualizar o valor na posição k para u
2. qual é o valor mínimo no intervalo [a, b]?

Entrada:
A primeira linha de entrada contém dois inteiros n e q: o número de valores e consultas.
A segunda linha tem n inteiros x_1, x_2, ..., x_n: os valores do array.
Finalmente, existem q linhas descrevendo as consultas. Cada linha possui três inteiros: ou "1 k u" ou "2 a b".

Saída:
Imprima o resultado de cada consulta do tipo 2.

Restrições:
1 <= n, q <= 2 * 10^5
1 <= x_i, u <= 10^9
1 <= k <= n
1 <= a <= b <= n
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 2e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<long long> tree(2 * n, INF);
    
    for (int i = 0; i < n; i++) {
        cin >> tree[n + i];
    }
    
    for (int i = n - 1; i > 0; --i) {
        tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
    }
    
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            long long u;
            cin >> k >> u;
            k--;
            for (tree[k += n] = u; k > 1; k >>= 1) {
                tree[k >> 1] = min(tree[k], tree[k ^ 1]);
            }
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            l--; 
            long long res = INF;
            for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res = min(res, tree[l++]);
                if (r & 1) res = min(res, tree[--r]);
            }
            cout << res << "\n";
        }
    }
    
    return 0;
}
/*
B - Consultas de Soma de Intervalo Dinâmico

Dado um array de n inteiros, sua tarefa é processar q consultas dos seguintes tipos:
1. atualizar o valor na posição k para u
2. qual é a soma dos valores no intervalo [a, b]?

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

using namespace std;

struct FenwickTree {
    int n;
    vector<long long> tree;
    
    FenwickTree(int n) {
        this->n = n;
        tree.assign(n + 1, 0);
    }
    
    void add(int i, long long delta) {
        for (; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }
    
    long long query(int i) {
        long long sum = 0;
        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    FenwickTree bit(n);
    vector<long long> a(n + 1);
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        bit.add(i, a[i]);
    }
    
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            long long u;
            cin >> k >> u;
            bit.add(k, u - a[k]);
            a[k] = u;
        } else if (type == 2) {
            int l, r;
            cin >> l >> r;
            cout << bit.query(r) - bit.query(l - 1) << "\n";
        }
    }
    
    return 0;
}
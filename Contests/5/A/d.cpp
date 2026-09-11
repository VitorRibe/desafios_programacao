/*
D - Consultas de Atualização de Intervalo

Dado um array de n inteiros, sua tarefa é processar q consultas dos seguintes tipos:
1. aumentar cada valor no intervalo [a, b] em u
2. qual é o valor na posição k?

Entrada:
A primeira linha de entrada contém dois inteiros n e q: o número de valores e consultas.
A segunda linha tem n inteiros x_1, x_2, ..., x_n: os valores do array.
Finalmente, existem q linhas descrevendo as consultas. Cada linha possui três inteiros: ou "1 a b u" ou "2 k".

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
    
    vector<long long> a(n + 1);
    FenwickTree bit(n + 1);
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            long long u;
            cin >> l >> r >> u;
            bit.add(l, u);
            bit.add(r + 1, -u);
        } else if (type == 2) {
            int k;
            cin >> k;
            cout << a[k] + bit.query(k) << "\n";
        }
    }
    
    return 0;
}
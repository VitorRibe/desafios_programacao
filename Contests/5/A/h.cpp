/*
H - O inimigo é fraco

Os romanos atacaram novamente. Desta vez eles são muito mais do que os persas, mas Shapur está pronto para derrotá-los. Ele diz: "Um leão nunca tem medo de cem ovelhas".
No entanto, Shapur tem que encontrar fraquezas no exército romano para derrotá-los. Então ele dá ao exército um número de fraqueza.
Na opinião de Shapur, a fraqueza de um exército é igual ao número de trios i, j, k tais que i < j < k e a_i > a_j > a_k onde a_x é o poder do homem posicionado na posição x.
O exército romano tem uma característica especial — os poderes de todas as pessoas nele são distintos.
Ajude Shapur a descobrir quão fracos são os romanos.

Entrada:
A primeira linha de entrada contém um único número n (3 <= n <= 10^6) — o número de homens no exército romano.
A próxima linha contém n inteiros positivos diferentes a_i (1 <= i <= n, 1 <= a_i <= 10^9) — poderes dos homens no exército romano.

Saída:
Um único número inteiro, a fraqueza do exército romano.
*/

#include <iostream>
#include <vector>
#include <algorithm>

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
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> a(n), vals(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        vals[i] = a[i];
    }
    
    sort(vals.begin(), vals.end());
    auto get_id = [&](int x) {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
    };
    
    vector<long long> greater_left(n), smaller_right(n);
    FenwickTree bit1(n), bit2(n);
    
    for (int i = 0; i < n; i++) {
        int id = get_id(a[i]);
        greater_left[i] = i - bit1.query(id);
        bit1.add(id, 1);
    }
    
    for (int i = n - 1; i >= 0; i--) {
        int id = get_id(a[i]);
        smaller_right[i] = bit2.query(id - 1);
        bit2.add(id, 1);
    }
    
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += greater_left[i] * smaller_right[i];
    }
    
    cout << ans << "\n";
    
    return 0;
}
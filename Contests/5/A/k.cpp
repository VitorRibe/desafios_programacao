/*
K - Consultas de Valores Distintos

Você recebe um array de n inteiros e q consultas da forma: quantos valores distintos existem em um intervalo [a, b]?

Entrada:
A primeira linha de entrada tem dois inteiros n e q: o tamanho do array e o número de consultas.
A próxima linha tem n inteiros x_1, x_2, ..., x_n: os valores do array.
Finalmente, existem q linhas descrevendo as consultas. Cada linha possui dois inteiros a e b.

Saída:
Para cada consulta, imprima o número de valores distintos no intervalo.

Restrições:
1 <= n, q <= 2 * 10^5
1 <= x_i <= 10^9
1 <= a <= b <= n
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct FenwickTree {
    int n;
    vector<int> tree;
    
    FenwickTree(int n) {
        this->n = n;
        tree.assign(n + 1, 0);
    }
    
    void add(int i, int delta) {
        for (; i <= n; i += i & -i) {
            tree[i] += delta;
        }
    }
    
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i) {
            sum += tree[i];
        }
        return sum;
    }
};

struct Query {
    int l, r, id;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<int> a(n + 1);
    vector<int> vals;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        vals.push_back(a[i]);
    }
    
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    
    auto get_id = [&](int x) {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
    };
    
    vector<vector<Query>> queries(n + 1);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries[r].push_back({l, r, i});
    }
    
    FenwickTree bit(n);
    vector<int> last_pos(vals.size() + 1, 0);
    vector<int> ans(q);
    
    for (int i = 1; i <= n; i++) {
        int val_id = get_id(a[i]);
        if (last_pos[val_id] != 0) {
            bit.add(last_pos[val_id], -1);
        }
        last_pos[val_id] = i;
        bit.add(i, 1);
        
        for (const auto& query : queries[i]) {
            ans[query.id] = bit.query(i) - bit.query(query.l - 1);
        }
    }
    
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
    
    return 0;
}
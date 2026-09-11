/*
I - DZY Ama Química

DZY tem n produtos químicos e m pares deles reagirão. O perigo de um tubo de ensaio vazio é 1. Toda vez que um produto químico é derramado e reage com algo já lá, o perigo é multiplicado por 2. Caso contrário, permanece como está.
Encontre o perigo máximo possível.

Entrada:
A primeira linha contém n e m.
As próximas m linhas indicam quais pares de produtos químicos reagem.

Saída:
Imprima um único inteiro — o perigo máximo possível.
*/
#include <iostream>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    DSU dsu(n);
    int components = n;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (dsu.unite(u, v)) {
            components--;
        }
    }

    long long max_danger = 1LL << (n - components);
    cout << max_danger << "\n";

    return 0;
}
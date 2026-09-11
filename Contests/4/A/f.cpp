/*
F - Estradas não apenas em Berland

O governo decidiu melhorar as relações com os países vizinhos construindo estradas para que seja possível alcançar todas as cidades. Há n cidades no total e exatamente n-1 estradas de mão dupla. Devido à crise, para construir uma nova estrada, uma antiga deve ser fechada. Determine o número mínimo de dias para reconstruir as estradas e desenhe um plano de fechamento e construção.

Entrada:
A primeira linha contém o inteiro n. As próximas n-1 linhas descrevem as estradas com inteiros a_i, b_i.

Saída:
Imprima o número t de dias necessários. Então imprima t linhas com o plano no formato i j u v (estrada i-j fechada, u-v construída).
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

    int n;
    if (!(cin >> n)) return 0;

    DSU dsu(n);
    vector<pair<int, int>> redundant_edges;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        if (!dsu.unite(u, v)) {
            redundant_edges.push_back({u, v});
        }
    }

    vector<int> components;
    for (int i = 1; i <= n; i++) {
        if (dsu.find(i) == i) {
            components.push_back(i);
        }
    }

    cout << redundant_edges.size() << "\n";
    for (size_t i = 0; i < redundant_edges.size(); i++) {
        cout << redundant_edges[i].first << " " << redundant_edges[i].second << " " 
             << components[i] << " " << components[i + 1] << "\n";
    }

    return 0;
}
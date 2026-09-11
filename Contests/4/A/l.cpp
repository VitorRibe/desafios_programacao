/*
L - Componentes Conexos

Já conhecemos a grande corporação onde Polycarpus trabalha como administrador de sistemas. A rede de computadores lá consiste em n computadores e m cabos que conectam alguns pares de computadores. Em outras palavras, a rede de computadores pode ser representada como um grafo não direcionado com n nós e m arestas. Vamos indexar os computadores com inteiros de 1 a n, e os cabos com inteiros de 1 a m.

Polycarpus recebeu uma tarefa importante — verificar a confiabilidade da rede de sua empresa. Para isso, ele decidiu realizar uma série de k experimentos na rede de computadores, onde o i-ésimo experimento ocorre da seguinte forma:
1. Desconectar temporariamente os cabos com índices de l_i a r_i, inclusive (os outros cabos permanecem conectados).
2. Contar o número de componentes conexos no grafo que define a rede de computadores naquele momento.
3. Reconectar os cabos desconectados de l_i a r_i (ou seja, restaurar a rede inicial).

Ajude Polycarpus a realizar todos os experimentos e para cada um imprima o número de componentes conexos. Vértices isolados devem ser contados como um único componente.

Entrada:
A primeira linha contém dois inteiros n, m (2 <= n <= 500; 1 <= m <= 10^4) — o número de computadores e o número de cabos.
As próximas m linhas contêm a descrição dos cabos. A i-ésima linha contém o par de inteiros x_i, y_i — os computadores conectados pelo i-ésimo cabo.
A próxima linha contém o inteiro k (1 <= k <= 2*10^4) — o número de experimentos. As próximas k linhas contêm as descrições dos experimentos. A i-ésima linha contém os inteiros l_i, r_i — os números dos cabos que Polycarpus desconecta.

Saída:
Imprima k números, o i-ésimo número representa o número de componentes conexos no i-ésimo experimento.
*/

#include <iostream>
#include <vector>

using namespace std;

struct DSU {
    int parent[505];
    int comps;
    
    void init(int n) {
        for (int i = 1; i <= n; i++) parent[i] = i;
        comps = n;
    }
    
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            comps--;
        }
    }
};

int u[10005], v[10005];
DSU pref[10005], suff[10005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= m; i++) {
        cin >> u[i] >> v[i];
    }

    pref[0].init(n);
    for (int i = 1; i <= m; i++) {
        pref[i] = pref[i - 1];
        pref[i].unite(u[i], v[i]);
    }

    suff[m + 1].init(n);
    for (int i = m; i >= 1; i--) {
        suff[i] = suff[i + 1];
        suff[i].unite(u[i], v[i]);
    }

    int k;
    cin >> k;
    while (k--) {
        int l, r;
        cin >> l >> r;
        
        DSU current = pref[l - 1];
        for (int i = 1; i <= n; i++) {
            current.unite(i, suff[r + 1].parent[i]);
        }
        
        cout << current.comps << "\n";
    }

    return 0;
}
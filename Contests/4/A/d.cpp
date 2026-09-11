/*
D - Distribuição de Notícias

Em alguma rede social, há n usuários se comunicando em m grupos de amigos. Inicialmente, um usuário x recebe a notícia de alguma fonte e envia aos amigos do mesmo grupo, e assim por diante. O processo termina quando não há par de amigos em que um sabe a notícia e o outro não.
Para cada usuário x, determine o número de usuários que saberão a notícia se inicialmente apenas o usuário x começar a distribuí-la.

Entrada:
A primeira linha contém dois inteiros n e m — o número de usuários e grupos.
Em seguida, m linhas seguem, cada uma começando com um inteiro k_i, o número de usuários no grupo, seguido pelos k_i inteiros que pertencem ao grupo.

Saída:
Imprima n inteiros. O i-ésimo inteiro deve ser igual ao número de usuários que saberão a notícia se o usuário i começar a distribuí-la.
*/
#include <iostream>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent, sz;
    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (sz[root_i] < sz[root_j])
                swap(root_i, root_j);
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    DSU dsu(n);

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        if (k > 0) {
            int first_user;
            cin >> first_user;
            for (int j = 1; j < k; j++) {
                int user;
                cin >> user;
                dsu.unite(first_user, user);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << dsu.sz[dsu.find(i)] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
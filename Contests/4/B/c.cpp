/*
C - Estranha Cadeia Alimentar (Strange Food Chain)

Existem 3 tipos de animais A, B e C. A pode comer B, B pode comer C, C pode comer A.
Agora temos n animais, numerados de 1 a n. Cada um deles é de um dos 3 tipos.
Hoje Mary nos conta k informações. Cada uma tem uma das duas formas:
1 x y: O tipo de x e y são o mesmo.
2 x y: x pode comer y.
Algumas informações são verdadeiras, outras falsas. Uma informação é falsa se satisfizer uma das 3 condições, caso contrário é verdadeira:
- X ou Y é maior que n.
- A informação diz que X pode comer X.
- A informação conflita com alguma informação verdadeira anterior.

Entrada:
O número de casos de teste t. Para cada bloco, n e k. k linhas seguintes, cada uma com D, X, Y.

Saída:
Para cada bloco, o número de informações falsas.
*/

#include <iostream>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> relation; 

    DSU(int n) {
        parent.resize(n + 1);
        relation.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        int root = find(parent[i]);
        relation[i] = (relation[i] + relation[parent[i]]) % 3;
        return parent[i] = root;
    }

    bool unite(int type, int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            if (type == 1 && relation[x] != relation[y]) return false;
            if (type == 2 && (relation[x] + 1) % 3 != relation[y]) return false;
            return true;
        }

        parent[rootY] = rootX;
        if (type == 1) {
            relation[rootY] = (relation[x] - relation[y] + 3) % 3;
        } else {
            relation[rootY] = (relation[x] - relation[y] + 4) % 3; 
        }
        return true;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    DSU dsu(n);
    int false_count = 0;

    for (int i = 0; i < k; i++) {
        int d, x, y;
        cin >> d >> x >> y;

        if (x > n || y > n) {
            false_count++;
            continue;
        }
        if (d == 2 && x == y) {
            false_count++;
            continue;
        }

        if (!dsu.unite(d, x, y)) {
            false_count++;
        }
    }
    cout << false_count << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
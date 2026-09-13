/*
G - Conjunto de Estatísticas de Ordem (Order statistic set)

Neste problema, você tem que manter um conjunto dinâmico de números que suporta as duas operações fundamentais:
- INSERT(S, x): se x não está em S, insira x em S
- DELETE(S, x): se x está em S, exclua x de S
e os dois tipos de consultas:
- K-TH(S): retorne o k-ésimo menor elemento de S
- COUNT(S, x): retorne o número de elementos de S menores que x

Entrada:
Linha 1: Q, o número de operações
Nas próximas Q linhas, o primeiro token de cada linha é um caractere I, D, K ou C, seguido por um espaço em branco e um inteiro que é o parâmetro para aquela operação.

Saída:
Para cada consulta, imprima o resultado correspondente. Para K-TH, se k for maior que o número de elementos, imprima 'invalid'.
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
    
    int find_kth(int k) {
        int pos = 0;
        for (int i = 18; i >= 0; i--) {
            if (pos + (1 << i) <= n && tree[pos + (1 << i)] < k) {
                pos += (1 << i);
                k -= tree[pos];
            }
        }
        return pos + 1;
    }
};

struct Query {
    char type;
    int x;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    vector<Query> queries(q);
    vector<int> vals;

    for (int i = 0; i < q; i++) {
        cin >> queries[i].type >> queries[i].x;
        if (queries[i].type != 'K') {
            vals.push_back(queries[i].x);
        }
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    auto get_id = [&](int x) {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
    };

    int max_compressed_id = vals.size();
    FenwickTree bit(max_compressed_id);
    vector<bool> present(max_compressed_id + 1, false);
    int total_elements = 0;

    for (int i = 0; i < q; i++) {
        char type = queries[i].type;
        int x = queries[i].x;

        if (type == 'I') {
            int id = get_id(x);
            if (!present[id]) {
                present[id] = true;
                bit.add(id, 1);
                total_elements++;
            }
        } 
        else if (type == 'D') {
            int id = get_id(x);
            if (present[id]) {
                present[id] = false;
                bit.add(id, -1);
                total_elements--;
            }
        } 
        else if (type == 'K') {
            if (x <= 0 || x > total_elements) {
                cout << "invalid\n";
            } else {
                int id = bit.find_kth(x);
                cout << vals[id - 1] << "\n";
            }
        } 
        else if (type == 'C') {
            int id = get_id(x);
            cout << bit.query(id - 1) << "\n";
        }
    }

    return 0;
}
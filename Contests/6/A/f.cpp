/*
F - Consultas de Salário (Salary Queries)

Uma empresa tem n funcionários com determinados salários. Sua tarefa é manter o registro dos salários e processar consultas.

Entrada:
A primeira linha de entrada contém dois inteiros n e q: o número de funcionários e consultas. Os funcionários são numerados de 1 a n.
A próxima linha tem n inteiros p_1, p_2, ..., p_n: o salário de cada funcionário.
Depois disso, existem q linhas descrevendo as consultas. Cada linha tem uma das seguintes formas:
- ! k x: alterar o salário do funcionário k para x
- ? a b: contar o número de funcionários cujo salário está entre a e b

Saída:
Imprima a resposta para cada consulta '?'.
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
    char type;
    int a, b;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<int> p(n + 1);
    vector<int> vals;
    
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        vals.push_back(p[i]);
    }
    
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].type >> queries[i].a >> queries[i].b;
        // Armazena os valores que aparecerão nas consultas para a compressão
        if (queries[i].type == '!') {
            vals.push_back(queries[i].b);
        } else {
            vals.push_back(queries[i].a);
            vals.push_back(queries[i].b);
        }
    }
    
    // Compressão de Coordenadas
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    
    // Função lambda para encontrar o índice comprimido
    auto get_id = [&](int x) {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
    };
    
    FenwickTree bit(vals.size());
    for (int i = 1; i <= n; i++) {
        bit.add(get_id(p[i]), 1);
    }
    
    // Processamento das Consultas
    for (int i = 0; i < q; i++) {
        if (queries[i].type == '!') {
            int k = queries[i].a;
            int x = queries[i].b;
            
            // Remove o salário antigo e insere o novo na BIT
            bit.add(get_id(p[k]), -1);
            p[k] = x;
            bit.add(get_id(p[k]), 1);
            
        } else {
            int a = queries[i].a;
            int b = queries[i].b;
            
            // Calcula a soma no intervalo [a, b]
            cout << bit.query(get_id(b)) - bit.query(get_id(a) - 1) << "\n";
        }
    }
    
    return 0;
}
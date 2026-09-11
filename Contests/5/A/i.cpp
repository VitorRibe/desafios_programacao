/*
I - Sereja e Colchetes

Sereja possui uma sequência de colchetes s_1, s_2, ..., s_n, ou, em outras palavras, uma string s de comprimento n, consistindo de caracteres "(" e ")".
Sereja precisa responder m consultas, cada uma delas descrita por dois inteiros l_i, r_i (1 <= l_i <= r_i <= n).
A resposta para a i-ésima consulta é o comprimento da subsequência correta máxima de colchetes da sequência s_{l_i}, s_{l_i+1}, ..., s_{r_i}. Ajude Sereja a responder todas as consultas.

Entrada:
A primeira linha contém uma sequência de caracteres s_1, s_2, ..., s_n sem nenhum espaço. Cada caractere é "(" ou ")".
A segunda linha contém um inteiro m (1 <= m <= 10^5) — o número de consultas.
Cada uma das próximas m linhas contém um par de inteiros l_i, r_i — a descrição da i-ésima consulta.

Saída:
Imprima a resposta para cada questão em uma única linha. Imprima as respostas na ordem em que aparecem na entrada.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int ans, open, close;
};

vector<Node> tree;

Node merge(Node l, Node r) {
    Node res;
    int match = min(l.open, r.close);
    res.ans = l.ans + r.ans + 2 * match;
    res.open = l.open + r.open - match;
    res.close = l.close + r.close - match;
    return res;
}

void build(const string& s, int node, int start, int end) {
    if (start == end) {
        if (s[start] == '(') tree[node] = {0, 1, 0};
        else tree[node] = {0, 0, 1};
        return;
    }
    int mid = (start + end) / 2;
    build(s, 2 * node, start, mid);
    build(s, 2 * node + 1, mid + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return {0, 0, 0};
    if (l <= start && end <= r) return tree[node];
    int mid = (start + end) / 2;
    Node left = query(2 * node, start, mid, l, r);
    Node right = query(2 * node + 1, mid + 1, end, l, r);
    return merge(left, right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    if (!(cin >> s)) return 0;
    
    int n = s.length();
    tree.resize(4 * n);
    build(s, 1, 0, n - 1);
    
    int m;
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << query(1, 0, n - 1, l - 1, r - 1).ans << "\n";
    }
    
    return 0;
}
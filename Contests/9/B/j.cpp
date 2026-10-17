/*
J - Xor-MST

Grafo completo com n vértices e pesos das arestas definidos por a_i XOR a_j.
Encontre o peso da Minimum Spanning Tree (MST).
Usando o algoritmo de Boruvka numa Trie (Boruvka-Trie).

Entrada:
n.
a_1, a_2, ..., a_n.

Saída:
Peso da MST.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TrieNode {
    int ch[2];
    int l, r; 
    TrieNode() {
        ch[0] = ch[1] = -1;
        l = 1e9;
        r = -1;
    }
};

vector<TrieNode> trie;

void insert(int val, int idx) {
    int curr = 0;
    trie[0].l = min(trie[0].l, idx);
    trie[0].r = max(trie[0].r, idx);
    for (int i = 29; i >= 0; i--) {
        int bit = (val >> i) & 1;
        if (trie[curr].ch[bit] == -1) {
            trie[curr].ch[bit] = trie.size();
            trie.emplace_back();
        }
        curr = trie[curr].ch[bit];
        trie[curr].l = min(trie[curr].l, idx);
        trie[curr].r = max(trie[curr].r, idx);
    }
}

long long solve(int node, int bit, const vector<int>& a) {
    if (bit < 0 || node == -1) return 0;
    
    int left_child = trie[node].ch[0];
    int right_child = trie[node].ch[1];
    
    if (left_child != -1 && right_child != -1) {
        int min_xor = (1 << 30);
        for (int i = trie[left_child].l; i <= trie[left_child].r; i++) {
            int curr = right_child;
            int curr_xor = (1 << bit);
            for (int j = bit - 1; j >= 0; j--) {
                int b = (a[i] >> j) & 1;
                if (trie[curr].ch[b] != -1) {
                    curr = trie[curr].ch[b];
                } else {
                    curr = trie[curr].ch[1 - b];
                    curr_xor |= (1 << j);
                }
            }
            min_xor = min(min_xor, curr_xor);
        }
        return min_xor + solve(left_child, bit - 1, a) + solve(right_child, bit - 1, a);
    } else if (left_child != -1) {
        return solve(left_child, bit - 1, a);
    } else if (right_child != -1) {
        return solve(right_child, bit - 1, a);
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    n = a.size();

    trie.emplace_back();
    for (int i = 0; i < n; i++) {
        insert(a[i], i);
    }

    cout << solve(0, 29, a) << "\n";

    return 0;
}
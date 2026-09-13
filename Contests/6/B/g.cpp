/*
G - Removendo Letras

Petya tem uma string de comprimento n. Ele realiza m operações descritas por l, r, e um caractere c: remover todos os caracteres c nas posições atuais entre l e r, inclusive. O comprimento diminui.
Determine como a string ficará após realizar todas as m operações.

Entrada:
A primeira linha contém dois inteiros n e m (1 <= n, m <= 2*10^5).
A segunda linha contém a string. As próximas m linhas contêm l, r e o caractere c.

Saída:
A string final após todas as operações.
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 200005;
int bit[MAXN];
int n, m;

void add(int i, int delta) {
    for (; i <= n; i += i & -i) {
        bit[i] += delta;
    }
}

int find_kth(int k) {
    int pos = 0;
    for (int i = 18; i >= 0; i--) {
        if (pos + (1 << i) <= n && bit[pos + (1 << i)] < k) {
            pos += (1 << i);
            k -= bit[pos];
        }
    }
    return pos + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    string s;
    cin >> s;

    set<int> pos[256];
    for (int i = 0; i < n; i++) {
        pos[(unsigned char)s[i]].insert(i + 1);
        add(i + 1, 1);
    }

    for (int i = 0; i < m; i++) {
        int l, r;
        char c;
        cin >> l >> r >> c;

        int orig_l = find_kth(l);
        int orig_r = find_kth(r);

        unsigned char uc = c;
        auto it = pos[uc].lower_bound(orig_l);
        
        while (it != pos[uc].end() && *it <= orig_r) {
            add(*it, -1);
            it = pos[uc].erase(it);
        }
    }

    string res = "";
    for (int i = 1; i <= n; i++) {
        if (find_kth(1) == i) { 
            res += s[i - 1];
            add(i, -1); 
        }
    }

    cout << res << "\n";

    return 0;
}
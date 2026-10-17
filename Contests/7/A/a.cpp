/*
A - Consultas de Caracteres Distintos

É dada uma string s consistindo de letras latinas minúsculas e q consultas para esta string.

Lembre-se de que a substring s[l; r] da string s é a string s_l s_{l+1} ... s_r. Por exemplo, as substrings de "codeforces" são "code", "force", "f", "for", mas não "coder" e "top".

Existem dois tipos de consultas:
- 1 pos c (1 <= pos <= |s|, c é uma letra latina minúscula): substitua s_pos por c (defina s_pos := c);
- 2 l r (1 <= l <= r <= |s|): calcule o número de caracteres distintos na substring s[l; r].

Entrada:
A primeira linha da entrada contém uma string s consistindo de no máximo 10^5 letras latinas minúsculas.
A segunda linha da entrada contém um número inteiro q (1 <= q <= 10^5) — o número de consultas.
As próximas q linhas contêm as consultas, uma por linha. Cada consulta é dada no formato descrito no enunciado do problema. É garantido que há pelo menos uma consulta do segundo tipo.

Saída:
Para cada consulta do segundo tipo, imprima a resposta para ela — o número de caracteres distintos na substring requisitada nessa consulta.
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.length();
    vector<set<int>> pos(26);

    for (int i = 0; i < n; i++) {
        pos[s[i] - 'a'].insert(i + 1);
    }

    int q;
    cin >> q;

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int p;
            char c;
            cin >> p >> c;

            char old_char = s[p - 1];
            pos[old_char - 'a'].erase(p);
            s[p - 1] = c;
            pos[c - 'a'].insert(p);
        } else {
            int l, r;
            cin >> l >> r;

            int count = 0;
            for (int i = 0; i < 26; i++) {
                auto it = pos[i].lower_bound(l);
                if (it != pos[i].end() && *it <= r) {
                    count++;
                }
            }
            cout << count << "\n";
        }
    }

    return 0;
}
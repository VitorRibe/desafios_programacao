/*
J - Aulas de Educação Física

Este ano Alex terminou a escola e agora é estudante universitário. Ele ainda tem que frequentar aulas de educação física e não assistiu a nenhuma! 
Existem n dias antes do fim do semestre, inicialmente todos são dias úteis. A equipe publica q ordens:
- k=1: todos os dias de l a r tornam-se não úteis.
- k=2: todos os dias de l a r tornam-se úteis.
Ajude Alex a determinar o número de dias úteis restantes após cada ordem!

Entrada:
A primeira linha contém n, e a segunda linha q — o número de dias e o número de ordens.
Em seguida, seguem q linhas com l_i, r_i e k_i.

Saída:
Imprima q inteiros. O i-ésimo deve ser igual ao número de dias úteis após as primeiras i ordens.
*/
#include <iostream>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    set<pair<int, int>> s;
    s.insert({1, n});
    long long total = n;
    
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        
        auto it = s.lower_bound({l, 0});
        if (it != s.begin()) {
            it--;
            if (it->second < l) it++;
        }
        
        while (it != s.end() && it->first <= r) {
            int curl = it->first;
            int curr = it->second;
            total -= (curr - curl + 1);
            it = s.erase(it);
            if (curl < l) {
                s.insert({curl, l - 1});
                total += (l - 1 - curl + 1);
            }
            if (curr > r) {
                s.insert({r + 1, curr});
                total += (curr - (r + 1) + 1);
            }
        }
        
        if (k == 2) {
            s.insert({l, r});
            total += (r - l + 1);
        }
        cout << total << "\n";
    }
    return 0;
}
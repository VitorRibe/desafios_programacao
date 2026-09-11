/*
E - Playlist

Você recebe a playlist de uma estação de rádio desde a sua criação. A playlist tem um total de n músicas.
Qual é a sequência mais longa de músicas sucessivas onde cada música é única?

Entrada:
A primeira linha de entrada contém um inteiro n: o número de músicas.
A próxima linha contém n inteiros k_1, k_2, ..., k_n: o número de identificação de cada música.

Saída:
Imprima o comprimento da sequência mais longa de músicas únicas.

Restrições:
1 <= n <= 2 * 10^5
1 <= k_i <= 10^9
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> k(n);
    for (int i = 0; i < n; i++) {
        cin >> k[i];
    }

    map<int, int> last_pos;
    int max_len = 0;
    int l = 0;

    for (int r = 0; r < n; r++) {
        if (last_pos.count(k[r])) {
            l = max(l, last_pos[k[r]] + 1);
        }
        last_pos[k[r]] = r;
        max_len = max(max_len, r - l + 1);
    }

    cout << max_len << "\n";

    return 0;
}
/*
Problema: E - Playlist (CSES - 1141)

Você recebe uma playlist de uma estação de rádio desde o seu estabelecimento. A playlist tem um total de n músicas.

Qual é a sequência mais longa de músicas sucessivas onde cada música é única?

Entrada
A primeira linha de entrada contém um inteiro n: o número de músicas.
A próxima linha tem n inteiros k_1, k_2, ..., k_n: o número de identificação de cada música.

Saída
Imprima o comprimento da sequência mais longa de músicas únicas.

Restrições
- 1 <= n <= 2 * 10^5
- 1 <= k_i <= 10^9
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

    map<int, int> last_pos;
    int start = 0;
    int ans = 0;

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        if (last_pos.count(k)) {
            start = max(start, last_pos[k] + 1);
        }
        ans = max(ans, i - start + 1);
        last_pos[k] = i;
    }

    cout << ans << "\n";

    return 0;
}
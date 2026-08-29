/*
Problema: E - Covered Points Count (CodeForces - 1000C)

Você recebe n segmentos em uma linha de coordenadas; cada ponto de extremidade de cada segmento tem coordenadas inteiras. Alguns segmentos podem degenerar a pontos. Os segmentos podem se cruzar, estar aninhados um no outro ou até coincidir.

Sua tarefa é a seguinte: para cada k pertencente a [1..n], calcule o número de pontos com coordenadas inteiras de tal forma que o número de segmentos que cobrem esses pontos seja igual a k. Um segmento com extremidades l_i e r_i cobre o ponto x se e somente se l_i <= x <= r_i.

Entrada
A primeira linha da entrada contém um inteiro n (1 <= n <= 2 * 10^5) — o número de segmentos.
As próximas n linhas contêm segmentos. A i-ésima linha contém um par de inteiros l_i, r_i (0 <= l_i <= r_i <= 10^{18}) — as extremidades do i-ésimo segmento.

Saída
Imprima n inteiros separados por espaço cnt_1, cnt_2, ..., cnt_n, onde cnt_i é igual ao número de pontos de tal forma que o número de segmentos que cobrem esses pontos seja igual a i.
*/

#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    map<long long, int> sweep;
    for (int i = 0; i < n; ++i) {
        long long l, r;
        cin >> l >> r;
        sweep[l]++;
        sweep[r + 1]--;
    }

    vector<long long> ans(n + 1, 0);
    int current_coverage = 0;
    long long last_x = -1;

    for (auto const& [x, val] : sweep) {
        if (last_x != -1 && current_coverage > 0) {
            ans[current_coverage] += (x - last_x);
        }
        current_coverage += val;
        last_x = x;
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
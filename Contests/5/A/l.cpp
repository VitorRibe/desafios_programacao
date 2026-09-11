/*
L - Consultas de Mínimo de Intervalo Estático

Dado um array de n inteiros, sua tarefa é processar q consultas da forma: qual é o valor mínimo no intervalo [a, b]?

Entrada:
A primeira linha de entrada tem dois inteiros n e q: o número de valores e consultas.
A segunda linha tem n inteiros x_1, x_2, ..., x_n: os valores do array.
Finalmente, existem q linhas descrevendo as consultas. Cada linha possui dois inteiros a e b: qual é o valor mínimo no intervalo [a, b]?

Saída:
Imprima o resultado de cada consulta.

Restrições:
1 <= n, q <= 2 * 10^5
1 <= x_i <= 10^9
1 <= a <= b <= n
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<int> log_2(n + 1);
    log_2[1] = 0;
    for (int i = 2; i <= n; i++) {
        log_2[i] = log_2[i / 2] + 1;
    }
    
    vector<vector<int>> st(18, vector<int>(n));
    for (int i = 0; i < n; i++) {
        st[0][i] = a[i];
    }
    
    for (int i = 1; i <= 17; i++) {
        for (int j = 0; j + (1 << i) <= n; j++) {
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        int len = r - l + 1;
        int k = log_2[len];
        cout << min(st[k][l], st[k][r - (1 << k) + 1]) << "\n";
    }
    
    return 0;
}
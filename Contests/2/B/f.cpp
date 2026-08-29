/*
Problema: F - Grouping (AtCoder - dp_u)

Existem N coelhos, numerados de 1, 2, ..., N.

Para cada i, j (1 <= i, j <= N), a compatibilidade do Coelho i e j é descrita por um inteiro a_{i, j}. Aqui, a_{i, i} = 0 para cada i, e a_{i, j} = a_{j, i} para cada i e j.

Taro está dividindo os N coelhos em algum número de grupos. Aqui, cada coelho deve pertencer a exatamente um grupo. Após o agrupamento, para cada i e j (1 <= i < j <= N), Taro ganha a_{i, j} pontos se o Coelho i e j pertencerem ao mesmo grupo.

Encontre a pontuação total máxima possível de Taro.

Restrições
- Todos os valores na entrada são inteiros.
- 1 <= N <= 16
- |a_{i, j}| <= 10^9
- a_{i, i} = 0
- a_{i, j} = a_{j, i}

Entrada
A entrada é fornecida no seguinte formato:
N
a_{1, 1} ... a_{1, N}
:
a_{N, 1} ... a_{N, N}

Saída
Imprima a pontuação total máxima possível de Taro.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<long long>> a(n, vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    int num_masks = 1 << n;
    vector<long long> score(num_masks, 0);

    for (int mask = 0; mask < num_masks; ++mask) {
        for (int i = 0; i < n; ++i) {
            if ((mask & (1 << i)) != 0) {
                for (int j = i + 1; j < n; ++j) {
                    if ((mask & (1 << j)) != 0) {
                        score[mask] += a[i][j];
                    }
                }
            }
        }
    }

    vector<long long> dp(num_masks, -1e18);
    dp[0] = 0;

    for (int mask = 1; mask < num_masks; ++mask) {
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
            dp[mask] = max(dp[mask], dp[mask ^ sub] + score[sub]);
        }
    }

    cout << dp[num_masks - 1] << "\n";

    return 0;
}
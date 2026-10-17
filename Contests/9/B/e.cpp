/*
E - Ranking the Cows

N vacas. FJ tem resultados para M pares. Quantas perguntas adicionais C ele precisa para ter certeza do ranking total?
Total de pares em DAG = N*(N-1)/2. Subtrair pares alcançáveis (Fecho Transitivo).

Entrada:
N, M.
M linhas X, Y (X > Y).

Saída:
Mínimo valor de C.
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        reach[u][v] = true;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (reach[i][k] && reach[k][j]) {
                    reach[i][j] = true;
                }
            }
        }
    }

    int known_pairs = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (reach[i][j] || reach[j][i]) {
                known_pairs++;
            }
        }
    }

    cout << (n * (n - 1)) / 2 - known_pairs << "\n";

    return 0;
}
/*
J - Removendo Dígitos

Você recebe um inteiro n. Em cada passo, você pode subtrair um dos dígitos do número do próprio número.
Quantos passos são necessários para tornar o número igual a 0?

Entrada:
A única linha de entrada possui o inteiro n.

Saída:
Imprima um inteiro: o número mínimo de passos.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> dp(n + 1, 1e9);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int temp = i;
        while (temp > 0) {
            int digit = temp % 10;
            if (digit > 0) {
                dp[i] = min(dp[i], dp[i - digit] + 1);
            }
            temp /= 10;
        }
    }

    cout << dp[n] << "\n";

    return 0;
}
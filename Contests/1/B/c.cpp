/*
Problema: C - Factory Machines (CSES - 1620)

Uma fábrica tem n máquinas que podem ser usadas para fazer produtos. Seu objetivo é fazer um total de t produtos.

Para cada máquina, você sabe o número de segundos que ela precisa para fazer um único produto. As máquinas podem trabalhar simultaneamente e você pode decidir livremente o cronograma delas.

Qual é o menor tempo necessário para fazer t produtos?

Entrada
A primeira linha de entrada tem dois inteiros n e t: o número de máquinas e de produtos.
A próxima linha tem n inteiros k_1, k_2, ..., k_n: o tempo necessário para fazer um produto usando cada máquina.

Saída
Imprima um inteiro: o tempo mínimo necessário para fazer t produtos.

Restrições
- 1 <= n <= 2 * 10^5
- 1 <= t <= 10^9
- 1 <= k_i <= 10^9
*/
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    long long t;
    if (!(cin >> n >> t)) return 0;

    vector<long long> k(n);
    for (int i = 0; i < n; i++) {
        cin >> k[i];
    }

    long long low = 1;
    long long high = 1e18;
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long products = 0;

        for (int i = 0; i < n; i++) {
            products += mid / k[i];
            
            if (products >= t) {
                break;
            }
        }

        if (products >= t) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
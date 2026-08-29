/*
Problema: H - Concert Tickets (CSES - 1091)

Existem n ingressos disponíveis, cada um com um determinado preço. Depois, m clientes chegam, um após o outro.

Cada cliente anuncia o preço máximo que está disposto a pagar por um ingresso e, após isso, ele ganha um ingresso com o preço mais próximo possível que não exceda o preço máximo.

Entrada
A primeira linha contém os inteiros n e m: o número de ingressos e o número de clientes.
A próxima linha contém n inteiros h_1, h_2, ..., h_n: o preço de cada ingresso.
A última linha contém m inteiros t_1, t_2, ..., t_m: o preço máximo para cada cliente na ordem em que chegam.

Saída
Imprima, para cada cliente, o preço que ele pagará pelo ingresso. Depois disso, o ingresso não pode ser comprado novamente.
Se um cliente não puder obter nenhum ingresso, imprima -1.

Restrições
- 1 <= n, m <= 2 * 10^5
- 1 <= h_i, t_i <= 10^9
*/
#include <iostream>
#include <set>

using namespace std;

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    multiset<int> tickets;
    for (int i = 0; i < n; i++) {
        int price;
        cin >> price;
        tickets.insert(price);
    }

    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;

        auto it = tickets.upper_bound(t);
        
        if (it == tickets.begin()) {
            cout << -1 << "\n";
        } else {
            it--;
            cout << *it << "\n";
            tickets.erase(it);
        }
    }

    return 0;
}
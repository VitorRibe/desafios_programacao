/*
  Problema: E - Room Allocation
  
  Há um grande hotel e n clientes chegarão em breve. Cada cliente deseja ter um quarto individual.
  Você conhece o dia de chegada e de partida de cada cliente. Dois clientes podem ficar no mesmo quarto 
  se o dia de partida do primeiro cliente for anterior ao dia de chegada do segundo cliente.
  
  Qual é o número mínimo de quartos necessários para acomodar todos os clientes? E como os quartos podem ser alocados?
  
  Entrada
  A primeira linha de entrada contém um inteiro n: o número de clientes.
  Depois há n linhas, cada uma descrevendo um cliente. Cada linha tem dois inteiros a e b: o dia de chegada e de partida.
  
  Saída
  Imprima primeiro um inteiro k: o número mínimo de quartos necessários.
  Depois disso, imprima uma linha contendo o número do quarto de cada cliente na mesma ordem da entrada. 
  Os quartos são numerados de 1, 2, ..., k. Você pode imprimir qualquer solução válida.
  
  Restrições
  - 1 <= n <= 2 * 10^5
  - 1 <= a <= b <= 10^9
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Customer {
    int arrival, departure, id;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Customer> customers(n);
    for (int i = 0; i < n; ++i) {
        cin >> customers[i].arrival >> customers[i].departure;
        customers[i].id = i;
    }

    sort(customers.begin(), customers.end(), [](const Customer& x, const Customer& y) {
        return x.arrival < y.arrival;
    });

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> rooms;

    vector<int> ans(n);
    int next_room = 1;

    for (int i = 0; i < n; ++i) {
        if (rooms.empty() || rooms.top().first >= customers[i].arrival) {
            rooms.push({customers[i].departure, next_room});
            ans[customers[i].id] = next_room;
            next_room++;
        } else {
            int room = rooms.top().second;
            rooms.pop();
            rooms.push({customers[i].departure, room});
            ans[customers[i].id] = room;
        }
    }

    cout << next_room - 1 << "\n";
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
    return 0;
}
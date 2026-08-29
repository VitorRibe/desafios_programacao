/*
  Problema: C - Traffic Lights
  
  Há uma rua de comprimento x cujas posições são numeradas de 0, 1, ..., x. Inicialmente não há semáforos, 
  mas n conjuntos de semáforos são adicionados à rua um após o outro.
  
  Sua tarefa é calcular o comprimento da passagem mais longa sem semáforos após cada adição.
  
  Entrada
  A primeira linha de entrada contém dois inteiros x e n: o comprimento da rua e o número de conjuntos de semáforos.
  A próxima linha contém n inteiros p_1, p_2, ..., p_n: a posição de cada conjunto de semáforos. Cada posição é distinta.
  
  Saída
  Imprima o comprimento da passagem mais longa sem semáforos após cada adição.
  
  Restrições
  - 1 <= x <= 10^9
  - 1 <= n <= 2 * 10^5
  - 0 < p_i < x
 */
#include <iostream>
#include <set>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int x, n;
    if (!(cin >> x >> n)) return 0;

    set<int> positions;
    multiset<int> lengths;

    positions.insert(0);
    positions.insert(x);
    lengths.insert(x);

    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;

        auto it = positions.upper_bound(p);
        int right = *it;
        int left = *prev(it);

        lengths.erase(lengths.find(right - left));

        lengths.insert(p - left);
        lengths.insert(right - p);

        positions.insert(p);
        cout << *lengths.rbegin() << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
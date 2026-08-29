/*
  Problema: A - Distinct Numbers
  
  Você recebe uma lista de n inteiros e 
  sua tarefa é calcular o número de 
  valores distintos na lista.
  
  Entrada
  A primeira linha de entrada possui um inteiro n: o número de valores.
  A segunda linha possui n inteiros x_1, x_2, ..., x_n.
  
  Saída
  Imprima um inteiro: o número de valores distintos.
  
  Restrições
  - 1 <= n <= 2  10^5
  - 1 <= x_i <= 10^9
 */
#include <iostream>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    set<int> distinct_values;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        distinct_values.insert(x);
    }
    cout << distinct_values.size() << "\n";
    return 0;
}
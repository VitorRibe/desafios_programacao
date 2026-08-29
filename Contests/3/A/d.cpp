/*
  Problema: D - Towers
  
  Você recebe n cubos em uma certa ordem, e sua tarefa é construir torres com eles. 
  Sempre que dois cubos estão um sobre o outro, o cubo superior deve ser menor que o cubo inferior.
  
  Você deve processar os cubos na ordem dada. Você sempre pode colocar o cubo no topo de uma torre existente 
  ou iniciar uma nova torre. Qual é o número mínimo possível de torres?
  
  Entrada
  A primeira linha de entrada contém um inteiro n: o número de cubos.
  A próxima linha contém n inteiros k_1, k_2, ..., k_n: os tamanhos dos cubos.
  
  Saída
  Imprima um inteiro: o número mínimo de torres.
  
  Restrições
  - 1 <= n <= 2 * 10^5
  - 1 <= k_i <= 10^9
 */
#include <iostream>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    multiset<int> towers;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;

        auto it = towers.upper_bound(k);
        if (it != towers.end()) {
            towers.erase(it);
        }
        towers.insert(k);
    }
    cout << towers.size() << "\n";
    return 0;
}
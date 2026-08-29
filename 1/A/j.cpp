/*
Problema: J - Apple Division (CSES - 1623)

Existem n maçãs com pesos conhecidos. Sua tarefa é dividir as maçãs em dois grupos para que a diferença entre os pesos dos grupos seja mínima.

Entrada
A primeira linha de entrada possui um inteiro n: o número de maçãs.
A próxima linha possui n inteiros p_1, p_2, ..., p_n: o peso de cada maçã.

Saída
Imprima um inteiro: a diferença mínima entre os pesos dos grupos.

Restrições
- 1 <= n <= 20
- 1 <= p_i <= 10^9
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<long long> p(n);
    long long total_sum = 0;
    
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        total_sum += p[i];
    }

    long long min_diff = -1;
    int limit = 1 << n;
    
    for (int mask = 0; mask < limit; mask++) {
        long long group1_sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                group1_sum += p[i];
            }
        }

        long long group2_sum = total_sum - group1_sum;
        long long current_diff = abs(group1_sum - group2_sum);
        
        if (min_diff == -1 || current_diff < min_diff) {
            min_diff = current_diff;
        }
    }
    cout << min_diff << "\n";
    return 0;
}
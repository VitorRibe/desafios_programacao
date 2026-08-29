/*
Problema: E - Collecting Numbers (CSES - 2216)

Você recebe um array que contém cada número entre 1 ... n exatamente uma vez. Sua tarefa é coletar os números de 1 a n em ordem crescente.

Em cada rodada, você percorre o array da esquerda para a direita e coleta o maior número possível de elementos. Qual será o número total de rodadas?

Entrada
A primeira linha possui um inteiro n: o tamanho do array.
A próxima linha possui n inteiros x_1, x_2, ..., x_n: os números no array.

Saída
Imprima um inteiro: o número de rodadas.

Restrições
- 1 <= n <= 2 * 10^5
*/
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        pos[x] = i;
    }

    int rounds = 1;
    for (int i = 1; i < n; i++) {
        if (pos[i] > pos[i + 1]) {
            rounds++;
        }
    }

    cout << rounds << "\n";

    return 0;
}
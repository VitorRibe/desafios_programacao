/*
Problema: C - Repetitions (CSES - 1069)

Você recebe uma sequência de DNA: uma string consistindo dos caracteres A, C, G e T. Sua tarefa é encontrar a repetição mais longa na sequência. Esta é uma substring de comprimento máximo contendo apenas um tipo de caractere.

Entrada
A única linha de entrada contém uma string de n caracteres.

Saída
Imprima um inteiro: o comprimento da repetição mais longa.

Restrições
- 1 <= n <= 10^6
*/
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    if (!(cin >> s)) return 0;

    int max_len = 0;
    int current_len = 0;

    for (size_t i = 0; i < s.length(); i++) {
        if (i == 0 || s[i] == s[i - 1]) {
            current_len++;
        } else {
            current_len = 1;
        }
        
        if (current_len > max_len) {
            max_len = current_len;
        }
    }

    cout << max_len << "\n";

    return 0;
}
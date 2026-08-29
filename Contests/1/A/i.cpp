/*
Problema: I - Creating Strings (CSES - 1622)

Dada uma string, sua tarefa é gerar todas as strings diferentes que podem ser criadas usando seus caracteres.

Entrada
A única linha de entrada possui uma string de comprimento n. Cada caractere está entre a-z.

Saída
Primeiro imprima um inteiro k: o número de strings. Em seguida, imprima k linhas: as strings em ordem alfabética.

Restrições
- 1 <= n <= 8
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string s;
    if (!(cin >> s)) return 0;

    sort(s.begin(), s.end());
    vector<string> perms;
    do {
        perms.push_back(s);
    } while (next_permutation(s.begin(), s.end()));
    cout << perms.size() << "\n";
    for (const string& p : perms) {
        cout << p << "\n";
    }
    return 0;
}
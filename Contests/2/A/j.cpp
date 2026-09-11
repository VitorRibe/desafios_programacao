/*
J - Livros

Quando Valera tem tempo livre, ele vai à biblioteca ler alguns livros. Hoje ele tem t minutos livres para ler. Por isso, Valera pegou n livros da biblioteca e estimou o tempo necessário para ler cada um. Valera precisa de a_i minutos para ler o i-ésimo livro.
Valera decidiu escolher um livro arbitrário de número i e ler os livros sequencialmente a partir desse livro (i, i+1, i+2, ...). Ele para quando o tempo acabar ou terminar o n-ésimo livro. Ele só começa um livro se tiver tempo suficiente para terminá-lo.
Imprima o número máximo de livros que Valera pode ler.

Entrada:
A primeira linha contém dois inteiros n e t (1 <= n <= 10^5, 1 <= t <= 10^9) — o número de livros e o número de minutos livres. A segunda linha contém uma sequência de n inteiros a_1, a_2, ..., a_n (1 <= a_i <= 10^4).

Saída:
Imprima um único inteiro — o número máximo de livros que Valera pode ler.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long t;
    if (!(cin >> n >> t)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int l = 0;
    long long current_sum = 0;
    int max_books = 0;

    for (int r = 0; r < n; r++) {
        current_sum += a[r];
        while (current_sum > t) {
            current_sum -= a[l];
            l++;
        }
        max_books = max(max_books, r - l + 1);
    }

    cout << max_books << "\n";

    return 0;
}
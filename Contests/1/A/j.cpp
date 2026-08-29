/*
Problema: J - Books (CodeForces - 279B)

Quando Valera tem algum tempo livre, ele vai à biblioteca ler alguns livros. Hoje ele tem t minutos livres para ler. É por isso que Valera pegou n livros na biblioteca e para cada livro ele estimou o tempo que vai precisar para ler. Vamos numerar os livros por inteiros de 1 a n. Valera precisa de a_i minutos para ler o i-ésimo livro.

Valera decidiu escolher um livro arbitrário com o número i e ler os livros um por um, a partir deste livro. Em outras palavras, ele lerá primeiro o livro número i, depois o livro número i + 1, depois o livro número i + 2 e assim por diante. Ele continua o processo até que seu tempo livre acabe ou ele termine de ler o n-ésimo livro. Valera lê cada livro até o fim, ou seja, ele não começa a ler o livro se não tiver tempo livre suficiente para terminar de lê-lo.

Imprima o número máximo de livros que Valera pode ler.

Entrada
A primeira linha contém dois inteiros n e t (1 <= n <= 10^5; 1 <= t <= 10^9) — o número de livros e o número de minutos livres que Valera tem. A segunda linha contém uma sequência de n inteiros a_1, a_2, ..., a_n (1 <= a_i <= 10^4), onde o número a_i mostra o número de minutos que o menino precisa para ler o i-ésimo livro.

Saída
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
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int left = 0;
    long long current_sum = 0;
    int max_books = 0;

    for (int right = 0; right < n; ++right) {
        current_sum += a[right];

        while (current_sum > t) {
            current_sum -= a[left];
            left++;
        }

        max_books = max(max_books, right - left + 1);
    }

    cout << max_books << "\n";

    return 0;
}
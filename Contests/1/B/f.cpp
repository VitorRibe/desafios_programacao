/*
Problema: F - Special Permutation (CodeForces - 1352G)

Uma permutação de comprimento n é um array p = [p_1, p_2, ..., p_n], que contém todos os inteiros de 1 a n (inclusive) e, além disso, cada número aparece exatamente uma vez. Por exemplo, p = [3, 1, 4, 2, 5] é uma permutação de comprimento 5.

Para um dado número n (n >= 2), encontre uma permutação p na qual a diferença absoluta de quaisquer dois elementos vizinhos (adjacentes) esteja entre 2 e 4, inclusive. Formalmente, encontre uma permutação p tal que 2 <= |p_i - p_{i+1}| <= 4 para cada i (1 <= i < n).

Imprima qualquer permutação desse tipo para o inteiro fornecido n ou determine que ela não existe.

Entrada
A primeira linha contém um inteiro t (1 <= t <= 100) — o número de casos de teste na entrada. Em seguida, seguem t casos de teste.
Cada caso de teste é descrito por uma única linha contendo um inteiro n (2 <= n <= 1000).

Saída
Imprima t linhas. Imprima uma permutação que atenda aos requisitos dados. Se houver várias dessas permutações, imprima qualquer uma delas. Se não existir tal permutação, imprima -1.
*/
#include <iostream>

using namespace std;

void solve() {
    int n;
    cin >> n;

    if (n < 4) {
        cout << -1 << "\n";
        return;
    }

    for (int i = n; i >= 1; i--) {
        if (i % 2 != 0) {
            cout << i << " ";
        }
    }

    cout << 4 << " " << 2 << " ";

    for (int i = 6; i <= n; i += 2) {
        cout << i << " ";
    }

    cout << "\n";
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
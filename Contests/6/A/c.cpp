/*
C - Semáforos (Traffic Lights)

Há uma rua de comprimento x cujas posições são numeradas de 0 a x. Inicialmente não há semáforos, mas n conjuntos de semáforos são adicionados à rua um após o outro.
Sua tarefa é calcular o comprimento da passagem mais longa sem semáforos após cada adição.

Entrada:
A primeira linha de entrada contém dois inteiros x e n: o comprimento da rua e o número de conjuntos de semáforos.
Em seguida, a próxima linha contém n inteiros p_1, p_2, ..., p_n: a posição de cada conjunto de semáforos. Cada posição é distinta.

Saída:
Imprima o comprimento da passagem mais longa sem semáforos após cada adição.
*/

#include <iostream>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int x, n;
    if (!(cin >> x >> n)) return 0;

    set<int> lights;
    lights.insert(0);
    lights.insert(x);

    multiset<int> gaps;
    gaps.insert(x);

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;

        auto it = lights.upper_bound(p);
        int right = *it;
        --it;
        int left = *it;

        gaps.erase(gaps.find(right - left));
        gaps.insert(p - left);
        gaps.insert(right - p);

        lights.insert(p);

        cout << *gaps.rbegin() << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
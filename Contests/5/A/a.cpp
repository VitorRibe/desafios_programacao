/*
Consultas de Soma de Intervalo Estático

Dado um array de n inteiros, sua tarefa é processar q consultas da forma: qual é a soma dos valores no intervalo [a, b]?

Entrada:
A primeira linha de entrada contém dois inteiros n e q: o número de valores e de consultas.
A segunda linha tem n inteiros x_1, x_2, ..., x_n: os valores do array.
Finalmente, existem q linhas descrevendo as consultas. Cada linha possui dois inteiros a e b: qual é a soma dos valores no intervalo [a, b]?

Saída:
Imprima o resultado de cada consulta.

Restrições:
1 <= n, q <= 2 * 10^5
1 <= x_i <= 10^9
1 <= a <= b <= n
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        long long x;
        cin >> x;
        prefix[i] = prefix[i - 1] + x;
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << prefix[b] - prefix[a - 1] << "\n";
    }

    return 0;
}
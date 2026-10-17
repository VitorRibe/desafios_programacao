/*
K - Mesmas Diferenças (Same Differences)

Você recebe um array a de n inteiros. Conte o número de pares de índices (i, j) tais que i < j e a_j - a_i = j - i.

Entrada
A primeira linha contém t, o número de casos de teste.
Para cada caso, a primeira linha contém n, e a segunda contém os n inteiros do array a.

Saída
Para cada caso, o número de pares válidos.
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        int n;
        cin >> n;
        
        map<int, long long> counts;
        long long pairs = 0;
        
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            // a_j - a_i = j - i  =>  a_j - j = a_i - i
            int val = a - i;
            pairs += counts[val];
            counts[val]++;
        }
        
        cout << pairs << "\n";
    }

    return 0;
}
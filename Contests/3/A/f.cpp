/*
  Problema: F - Nearest Smaller Values
  
  Dado um array de n inteiros, sua tarefa é encontrar para cada posição do array 
  a posição mais próxima à sua esquerda que possui um valor menor.
  
  Entrada
  A primeira linha de entrada possui um inteiro n: o tamanho do array.
  A segunda linha possui n inteiros x_1, x_2, ..., x_n: os valores do array.
  
  Saída
  Imprima n inteiros: para cada posição do array, a posição mais próxima com um valor menor. 
  Se não houver tal posição, imprima 0.
  
  Restrições
  - 1 <= n <= 2 * 10^5
  - 1 <= x_i <= 10^9
 */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    stack<pair<int, int>> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && st.top().first >= a[i]) {
            st.pop();
        }

        if (st.empty()) {
            cout << 0;
        } else {
            cout << st.top().second;
        }

        cout << (i == n - 1 ? "" : " ");
        st.push({a[i], i + 1});
    }
    cout << "\n";
    return 0;
}
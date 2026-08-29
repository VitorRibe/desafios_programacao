/*
  Problema: H - Subarrays
  
  Dado um array e um inteiro k, encontre o máximo para cada subarray contíguo de tamanho k.
  
  Entrada
  O número n denotando o número de elementos no array, depois em uma nova linha temos os números do array,
  e então k em uma nova linha.
  
  Restrições
  - n < 10^6 (Editado: na verdade, n <= 10^5)
  - k < 10^5
  - 1 <= k <= n
  - Cada elemento do array está entre 0 e 10^6
  
  Saída
  Imprima o array resultante com os máximos.
 */
#include <iostream>
#include <vector>
#include <deque>

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

    int k;
    if (!(cin >> k)) return 0;
    deque<int> dq;

    for (int i = 0; i < n; ++i) {
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        while (!dq.empty() && a[dq.back()] <= a[i]) {
            dq.pop_back();
        }
        dq.push_back(i);

        if (i >= k - 1) {
            cout << a[dq.front()] << (i == n - 1 ? "" : " ");
        }
    }
    cout << "\n";
    return 0;
}
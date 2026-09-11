/*
E - Contagem de Inversões

Seja A[0 ... n - 1] um array de n inteiros positivos distintos. Se i < j e A[i] > A[j] então o par (i, j) é chamado de inversão de A.
Dado n e um array A sua tarefa é encontrar o número de inversões de A.

Entrada:
A primeira linha contém t, o número de casos de teste seguido por um espaço em branco.
Cada um dos t testes começa com um número n (n <= 200000).
Em seguida, seguem n + 1 linhas. Na i-ésima linha um número A[i - 1] é dado (A[i - 1] <= 10^7).
A (n + 1)-ésima linha é um espaço em branco.

Saída:
Para cada teste produza uma linha dando o número de inversões de A.
*/

#include <iostream>
#include <vector>

using namespace std;

long long merge_and_count(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    long long inv = 0;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            inv += (n1 - i);
        }
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    return inv;
}

long long merge_sort_and_count(vector<int>& arr, int l, int r) {
    long long inv = 0;
    if (l < r) {
        int m = l + (r - l) / 2;
        inv += merge_sort_and_count(arr, l, m);
        inv += merge_sort_and_count(arr, m + 1, r);
        inv += merge_and_count(arr, l, m, r);
    }
    return inv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (!(cin >> t)) return 0;
    
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        cout << merge_sort_and_count(a, 0, n - 1) << "\n";
    }
    
    return 0;
}
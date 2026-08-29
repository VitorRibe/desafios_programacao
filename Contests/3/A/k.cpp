/*
  Problema: K - Inversion Count
  
  Seja A[0 ... n - 1] um array de n inteiros positivos distintos. Se i < j e A[i] > A[j] 
  então o par (i, j) é chamado de uma inversão de A. Dado n e um array A, sua tarefa é 
  encontrar o número de inversões de A.
  
  Entrada
  A primeira linha contém t, o número de casos de teste, seguido por um espaço em branco. 
  Cada um dos t testes começa com um número n (n <= 200000). Em seguida, seguem n + 1 linhas. 
  Na i-ésima linha é dado um número A[i - 1] (A[i - 1] <= 10^7). A (n + 1)-ésima linha é 
  um espaço em branco.
  
  Saída
  Para cada teste, imprima uma linha dando o número de inversões de A.
 */
#include <iostream>
#include <vector>

using namespace std;

long long merge_and_count(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;
    long long inversions = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        } else {
            temp.push_back(arr[j++]);
            inversions += (mid - i + 1);
        }
    }
    
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = left, p = 0; k <= right; k++, p++) {
        arr[k] = temp[p];
    }
    return inversions;
}

long long merge_sort_and_count(vector<int>& arr, int left, int right) {
    long long inversions = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        inversions += merge_sort_and_count(arr, left, mid);
        inversions += merge_sort_and_count(arr, mid + 1, right);
        inversions += merge_and_count(arr, left, mid, right);
    }
    return inversions;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cout << merge_sort_and_count(a, 0, n - 1) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
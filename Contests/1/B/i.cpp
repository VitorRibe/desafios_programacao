/*
Problema: I - Aggressive cows (SPOJ - AGGRCOW)

O Fazendeiro John construiu um novo e longo celeiro, com N (2 <= N <= 100.000) baias. As baias estão localizadas ao longo de uma linha reta nas posições x1 ... xN (0 <= xi <= 1.000.000.000).

Suas C (2 <= C <= N) vacas não gostam deste layout do celeiro e se tornam agressivas umas com as outras assim que são colocadas em uma baia. Para evitar que as vacas se machuquem, FJ quer atribuir as vacas às baias de forma que a distância mínima entre duas delas seja a maior possível. Qual é a maior distância mínima?

Entrada
t – o número de casos de teste, em seguida, seguem t casos de teste.
- Linha 1: Dois inteiros separados por espaço: N e C
- Linhas 2..N+1: A linha i+1 contém um inteiro da localização da baia, xi

Saída
Para cada caso de teste imprima um inteiro: a maior distância mínima.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool check(int d, const vector<int>& stalls, int c) {
    int count = 1;
    int last_pos = stalls[0];
    
    for (int i = 1; i < stalls.size(); i++) {
        if (stalls[i] - last_pos >= d) {
            count++;
            last_pos = stalls[i];
            if (count == c) {
                return true;
            }
        }
    }
    return false;
}

void solve() {
    int n, c;
    cin >> n >> c;
    
    vector<int> stalls(n);
    for (int i = 0; i < n; i++) {
        cin >> stalls[i];
    }
    
    sort(stalls.begin(), stalls.end());
    
    int low = 1;
    int high = stalls[n - 1] - stalls[0];
    int ans = 0;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (check(mid, stalls, c)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    cout << ans << "\n";
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
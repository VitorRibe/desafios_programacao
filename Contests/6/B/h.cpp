/*
H - Construção Máxima I

Você recebe o mapa de uma floresta onde alguns quadrados estão vazios e alguns têm árvores.
Qual é a área máxima de uma construção retangular que pode ser colocada na floresta para que nenhuma árvore seja cortada?

Entrada:
A primeira linha de entrada contém inteiros n e m: o tamanho da floresta.
Depois disso, a floresta é descrita. Cada quadrado está vazio (.) ou tem árvores (*).

Saída:
Imprima a área máxima de uma construção retangular.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<int> height(m, 0);
    long long max_area = 0;

    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;

        for (int j = 0; j < m; j++) {
            if (row[j] == '.') {
                height[j]++;
            } else {
                height[j] = 0;
            }
        }

        vector<int> st;
        vector<int> left(m), right(m);

        for (int j = 0; j < m; j++) {
            while (!st.empty() && height[st.back()] >= height[j]) {
                st.pop_back();
            }
            left[j] = st.empty() ? 0 : st.back() + 1;
            st.push_back(j);
        }

        st.clear();

        for (int j = m - 1; j >= 0; j--) {
            while (!st.empty() && height[st.back()] >= height[j]) {
                st.pop_back();
            }
            right[j] = st.empty() ? m - 1 : st.back() - 1;
            st.push_back(j);
        }

        for (int j = 0; j < m; j++) {
            max_area = max(max_area, (long long)height[j] * (right[j] - left[j] + 1));
        }
    }

    cout << max_area << "\n";

    return 0;
}
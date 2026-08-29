/*
  Problema: G - Maximum Building I
  
  Você recebe o mapa de uma floresta onde alguns quadrados estão vazios e alguns quadrados têm árvores.
  Qual é a área máxima de um edifício retangular que pode ser colocado na floresta para que nenhuma árvore precise ser cortada?
  
  Entrada
  A primeira linha de entrada contém os inteiros n e m: o tamanho da floresta.
  Depois disso, a floresta é descrita. Cada quadrado está vazio (.) ou tem árvores ().
  
  Saída
  Imprima a área máxima de um edifício retangular.
  
  Restrições
  - 1 <= n, m <= 1000
 */
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> forest(n);
    for (int i = 0; i < n; ++i) {
        cin >> forest[i];
    }

    vector<int> heights(m, 0);
    int max_area = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (forest[i][j] == '*') {
                heights[j] = 0;
            } else {
                heights[j]++;
            }
        }

        stack<int> st;
        for (int j = 0; j <= m; ++j) {
            int h = (j == m) ? 0 : heights[j];
            while (!st.empty() && heights[st.top()] >= h) {
                int tp = st.top();
                st.pop();
                int width = st.empty() ? j : (j - st.top() - 1);
                max_area = max(max_area, heights[tp] * width);
            }
            st.push(j);
        }
    }
    cout << max_area << "\n";
    return 0;
}
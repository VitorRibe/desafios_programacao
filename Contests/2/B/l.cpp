/*
Problema: L - Maximize the Largest Component (Easy Version) (CodeForces - 1985H1)

As versões fácil e difícil são problemas diferentes, portanto, leia as declarações de ambos os problemas completa e cuidadosamente. A única diferença entre as duas versões é a operação.

Alex tem uma grade com n linhas e m colunas consistindo de caracteres '.' e '#'. Um conjunto de células '#' forma um componente conectado se, de qualquer célula neste conjunto, for possível alcançar qualquer outra célula neste conjunto movendo-se apenas para outra célula no conjunto que compartilha um lado comum. O tamanho de um componente conectado é o número de células no conjunto.

Em uma operação, Alex seleciona qualquer linha r (1 <= r <= n) ou qualquer coluna c (1 <= c <= m), então define cada célula na linha r ou coluna c para ser '#'. Ajude Alex a encontrar o tamanho máximo possível do maior componente conectado de células '#' que ele pode alcançar após realizar a operação no máximo uma vez.

Entrada
A primeira linha da entrada contém um único inteiro t (1 <= t <= 10^4) — o número de casos de teste.
A primeira linha de cada caso de teste contém dois inteiros n e m (1 <= n * m <= 10^6) — o número de linhas e colunas da grade.
As próximas n linhas contêm m caracteres cada. Cada caractere é '.' ou '#'.
É garantido que a soma de n * m em todos os casos de teste não exceda 10^6.

Saída
Para cada caso de teste, imprima um único inteiro — o tamanho máximo possível de um componente conectado de células '#' que Alex pode alcançar.
*/

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void dfs(int r, int c, int n, int m, const vector<string>& grid, vector<vector<int>>& comp_id, int id, int& size) {
    comp_id[r][c] = id;
    size++;
    for (int i = 0; i < 4; ++i) {
        int nr = r + dx[i];
        int nc = c + dy[i];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == '#' && comp_id[nr][nc] == -1) {
            dfs(nr, nc, n, m, grid, comp_id, id, size);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    vector<vector<int>> comp_id(n, vector<int>(m, -1));
    vector<int> comp_size;

    int current_id = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '#' && comp_id[i][j] == -1) {
                int size = 0;
                dfs(i, j, n, m, grid, comp_id, current_id, size);
                comp_size.push_back(size);
                current_id++;
            }
        }
    }

    int max_ans = 0;

    for (int i = 0; i < n; ++i) {
        set<int> adjacent_comps;
        int dots = 0;
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                dots++;
            } else {
                adjacent_comps.insert(comp_id[i][j]);
            }
            if (i > 0 && grid[i - 1][j] == '#') adjacent_comps.insert(comp_id[i - 1][j]);
            if (i < n - 1 && grid[i + 1][j] == '#') adjacent_comps.insert(comp_id[i + 1][j]);
        }
        int current_ans = dots;
        for (int id : adjacent_comps) {
            current_ans += comp_size[id];
        }
        max_ans = max(max_ans, current_ans);
    }

    for (int j = 0; j < m; ++j) {
        set<int> adjacent_comps;
        int dots = 0;
        for (int i = 0; i < n; ++i) {
            if (grid[i][j] == '.') {
                dots++;
            } else {
                adjacent_comps.insert(comp_id[i][j]);
            }
            if (j > 0 && grid[i][j - 1] == '#') adjacent_comps.insert(comp_id[i][j - 1]);
            if (j < m - 1 && grid[i][j + 1] == '#') adjacent_comps.insert(comp_id[i][j + 1]);
        }
        int current_ans = dots;
        for (int id : adjacent_comps) {
            current_ans += comp_size[id];
        }
        max_ans = max(max_ans, current_ans);
    }

    cout << max_ans << "\n";
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
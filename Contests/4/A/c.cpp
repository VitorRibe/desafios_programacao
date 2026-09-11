/*
C - Patinação no Gelo

Bajtek está aprendendo a patinar no gelo. Como é iniciante, seu único modo de se mover é empurrar um monte de neve para o norte, sul, leste ou oeste e deslizar até pousar em outro monte de neve. Ele percebeu que é impossível chegar de alguns montes a outros. Ele agora quer amontoar montes de neve adicionais para poder ir de qualquer monte para qualquer outro. Encontre o número mínimo de montes de neve que precisam ser criados.

Entrada:
A primeira linha contém um único inteiro n (1 <= n <= 100) — o número de montes de neve. Cada uma das próximas n linhas contém dois inteiros x_i e y_i — as coordenadas do i-ésimo monte de neve.

Saída:
Imprima o número mínimo de montes de neve que precisam ser criados.
*/
#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
};

vector<Point> points;
vector<bool> visited;
int n;

void dfs(int u) {
    visited[u] = true;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && (points[u].x == points[v].x || points[u].y == points[v].y)) {
            dfs(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    points.resize(n);
    visited.assign(n, false);

    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    int components = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            components++;
            dfs(i);
        }
    }

    cout << components - 1 << "\n";

    return 0;
}
/*
A - Crachá (Badge)

Na escola, se um aluno se comporta mal, o professor faz um furo em seu crachá. Se um aluno é pego, ele acusa o aluno p_i.
O professor vai para p_i, e o processo continua até chegar a alguém que já tem um furo (que receberá o segundo furo).
Para cada aluno a como o primeiro pego, determine quem receberá o segundo furo.

Entrada:
n (número de alunos).
p_1, ..., p_n (quem cada aluno acusa).

Saída:
Para cada a de 1 a n, imprima quem recebe o segundo furo.
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    for (int i = 1; i <= n; i++) {
        vector<bool> visited(n + 1, false);
        int curr = i;
        while (!visited[curr]) {
            visited[curr] = true;
            curr = p[curr];
        }
        cout << curr << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
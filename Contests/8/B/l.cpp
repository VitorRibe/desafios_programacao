/*
L - Oito (Eight)

Escreva um programa para resolver o quebra-cabeça 8-puzzle (3x3).

Entrada:
N casos de teste.
Cada dataset tem uma configuração de 1 a 8 e 'x' (o espaço vazio).

Saída:
'unsolvable' se não tiver solução.
A sequência de movimentos (r, l, u, d) para resolver o puzzle.
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

const string GOAL = "12345678x";

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
char dir_char[] = {'u', 'd', 'l', 'r'};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        string start = "";
        for (int i = 0; i < 9; i++) {
            char c;
            cin >> c;
            start += c;
        }

        // Check solvability
        int inv = 0;
        for (int i = 0; i < 9; i++) {
            if (start[i] == 'x') continue;
            for (int j = i + 1; j < 9; j++) {
                if (start[j] == 'x') continue;
                if (start[i] > start[j]) inv++;
            }
        }

        if (inv % 2 != 0) {
            cout << "unsolvable\n";
            if (t > 0) cout << "\n";
            continue;
        }

        queue<string> q;
        map<string, char> move;
        map<string, string> parent;

        q.push(start);
        move[start] = 'S'; // Start

        bool found = false;

        while (!q.empty()) {
            string curr = q.front();
            q.pop();

            if (curr == GOAL) {
                found = true;
                break;
            }

            int x_pos = curr.find('x');
            int r = x_pos / 3;
            int c = x_pos % 3;

            for (int i = 0; i < 4; i++) {
                int nr = r + dx[i];
                int nc = c + dy[i];

                if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
                    string next_state = curr;
                    swap(next_state[x_pos], next_state[nr * 3 + nc]);

                    if (move.find(next_state) == move.end()) {
                        move[next_state] = dir_char[i];
                        parent[next_state] = curr;
                        q.push(next_state);
                    }
                }
            }
        }

        if (found) {
            string path = "";
            string curr = GOAL;
            while (curr != start) {
                path += move[curr];
                curr = parent[curr];
            }
            reverse(path.begin(), path.end());
            cout << path << "\n";
        } else {
            cout << "unsolvable\n"; // Fallback, shouldn't reach here if parity check is correct
        }

        if (t > 0) cout << "\n";
    }

    return 0;
}
/*
D - Buracos

O pequeno Petya gosta muito de jogar. Acima de tudo, ele gosta de jogar um jogo chamado «Buracos». Este é um jogo para uma pessoa com as seguintes regras:

Existem N buracos localizados em uma única fileira e numerados da esquerda para a direita com números de 1 a N. Cada buraco tem sua própria força (o buraco de número i tem a força a_i). Se você jogar uma bola no buraco i, ela saltará imediatamente para o buraco i + a_i, depois saltará para fora dele e assim por diante. Se não houver nenhum buraco com tal número, a bola simplesmente saltará para fora da fileira. Em cada uma das M jogadas, o jogador pode realizar uma de duas ações:

- Definir a força do buraco a para o valor b.
- Jogar uma bola no buraco a e contar o número de saltos da bola antes que ela saia da fileira e também anotar o número do buraco do qual ela saltou logo antes de sair da fileira.

Petya não é bom em matemática, então, como você já deve ter adivinhado, cabe a você realizar todos os cálculos.

Entrada:
A primeira linha contém dois inteiros N e M (1 <= N <= 10^5, 1 <= M <= 10^5) — o número de buracos em uma fileira e o número de jogadas. A segunda linha contém N inteiros positivos não excedendo N — os valores iniciais da força dos buracos. As M linhas seguintes descrevem as jogadas feitas por Petya. Cada uma dessas linhas pode ser de um dos dois tipos:
- 0 a b
- 1 a

O tipo 0 significa que é necessário definir a força do buraco a para b, e o tipo 1 significa que é necessário jogar uma bola no a-ésimo buraco. Os números a e b são inteiros positivos que não excedem N.

Saída:
Para cada jogada do tipo 1, imprima dois números separados por espaço em uma linha separada — o número do último buraco que a bola visitou antes de sair da fileira e o número de saltos que ela deu.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
const int BLK = 320;

int n, m;
int power[MAXN];
int next_hole[MAXN];
int jumps[MAXN];
int last_hole[MAXN];

void recompute_block(int b) {
    int start = b * BLK;
    int end = min(n - 1, (b + 1) * BLK - 1);
    for (int i = end; i >= start; i--) {
        int nxt = i + power[i];
        if (nxt > end) {
            next_hole[i] = nxt;
            jumps[i] = 1;
            last_hole[i] = i;
        } else {
            next_hole[i] = next_hole[nxt];
            jumps[i] = 1 + jumps[nxt];
            last_hole[i] = last_hole[nxt];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < n; i++) {
        cin >> power[i];
    }

    int num_blocks = (n + BLK - 1) / BLK;
    for (int b = 0; b < num_blocks; b++) {
        recompute_block(b);
    }

    while (m--) {
        int type;
        cin >> type;
        if (type == 0) {
            int a, b;
            cin >> a >> b;
            a--;
            power[a] = b;
            recompute_block(a / BLK);
        } else {
            int a;
            cin >> a;
            a--;
            int curr = a;
            int total_jumps = 0;
            int last = curr;
            while (curr < n) {
                last = last_hole[curr];
                total_jumps += jumps[curr];
                curr = next_hole[curr];
            }
            cout << (last + 1) << " " << total_jumps << "\n";
        }
    }

    return 0;
}
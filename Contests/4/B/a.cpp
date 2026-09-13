/*
A - Guerra (War)

Uma guerra está sendo travada entre dois países, A e B. Como um cidadão leal de C, você decide ajudar a espionagem do seu país participando das negociações de paz (incógnito, é claro). Existem n pessoas nas negociações (não incluindo você), mas você não sabe qual pessoa pertence a qual país. Você pode ver as pessoas conversando entre si, e através da observação de seus comportamentos durante suas conversas individuais ocasionais, você pode adivinhar se eles são amigos ou inimigos. Na verdade, o que seu país precisaria saber é se certos pares de pessoas são do mesmo país, ou se eles são inimigos. Você pode receber essas perguntas do governo de C mesmo durante as negociações de paz, e você tem que dar respostas com base em suas observações até o momento. Felizmente, ninguém fala com você, pois ninguém presta atenção à sua aparência humilde.

Agora, mais formalmente, considere uma caixa preta com as seguintes operações:

setFriends(x, y) - mostra que x e y são do mesmo país
setEnemies(x, y) - mostra que x e y são de países diferentes
areFriends(x, y) - retorna verdadeiro se você tem certeza de que x e y são amigos
areEnemies(x, y) - retorna verdadeiro se você tem certeza de que x e y são inimigos

As duas primeiras operações devem sinalizar um erro se contradizerem seu conhecimento anterior. As relações de amigos e inimigos obedecem às propriedades de equivalência e simetria (ex: inimigo do meu inimigo é meu amigo).

Entrada:
A primeira linha contém um único inteiro, n, o número de pessoas.
Cada uma das linhas seguintes contém um trio de inteiros, c x y, onde c é o código da operação:
c = 1, setFriends
c = 2, setEnemies
c = 3, areFriends
c = 4, areEnemies
e x e y são seus parâmetros, que são inteiros no intervalo [0, n), identificando duas pessoas (diferentes).
A última linha contém '0 0 0'.

Saída:
Para cada operação "areFriends" e "areEnemies", escreva '0' (significando não) ou '1' (significando sim) na saída.
Além disso, para cada operação "setFriends" ou "setEnemies" que contradiz o conhecimento anterior, produza um '-1' na saída; note que tal operação não deve produzir nenhum outro efeito e a execução deve continuar. Um "setFriends" ou "setEnemies" bem-sucedido não gera saída.
Todos os inteiros no arquivo de saída devem ser separados por uma quebra de linha.
*/

#include <iostream>
#include <vector>

using namespace std;

struct DSU {
    vector<int> parent;
    
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        DSU dsu(2 * n);
        int c, x, y;
        
        while (cin >> c >> x >> y && (c != 0 || x != 0 || y != 0)) {
            if (c == 1) {
                if (dsu.find(x) == dsu.find(y + n)) {
                    cout << -1 << "\n";
                } else {
                    dsu.unite(x, y);
                    dsu.unite(x + n, y + n);
                }
            } else if (c == 2) {
                if (dsu.find(x) == dsu.find(y)) {
                    cout << -1 << "\n";
                } else {
                    dsu.unite(x, y + n);
                    dsu.unite(x + n, y);
                }
            } else if (c == 3) {
                if (dsu.find(x) == dsu.find(y)) {
                    cout << 1 << "\n";
                } else {
                    cout << 0 << "\n";
                }
            } else if (c == 4) {
                if (dsu.find(x) == dsu.find(y + n)) {
                    cout << 1 << "\n";
                } else {
                    cout << 0 << "\n";
                }
            }
        }
    }

    return 0;
}
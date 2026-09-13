/*
L - Rede Social (versão difícil) (Social Network (hard version))

Você está enviando mensagens em uma rede social via smartphone. Seu smartphone pode mostrar no máximo k conversas mais recentes.
Você receberá n mensagens, a i-ésima mensagem será recebida do amigo com ID id_i.
Se você receber uma mensagem de um amigo que já está na tela, nada acontece.
Caso contrário, se a tela estiver cheia, a última conversa é removida. A conversa com id_i aparece na primeira posição e todas as outras descem uma posição.

Sua tarefa é encontrar a lista de conversas (na ordem em que são exibidas) após processar todas as n mensagens.

Entrada:
A primeira linha contém n e k. A segunda linha contém n inteiros id_1, ..., id_n.

Saída:
Na primeira linha, imprima m (o número de conversas exibidas). Na segunda linha, imprima as m IDs.
*/

#include <iostream>
#include <vector>
#include <deque>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    deque<int> screen;
    set<int> in_screen;

    for (int i = 0; i < n; i++) {
        int id;
        cin >> id;

        if (in_screen.count(id) == 0) {
            if (screen.size() == k) {
                int last = screen.back();
                screen.pop_back();
                in_screen.erase(last);
            }
            screen.push_front(id);
            in_screen.insert(id);
        }
    }

    cout << screen.size() << "\n";
    for (int i = 0; i < screen.size(); i++) {
        cout << screen[i] << (i + 1 == screen.size() ? "" : " ");
    }
    cout << "\n";

    return 0;
}
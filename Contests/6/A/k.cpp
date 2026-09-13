/*
K - Sistema de Registro (Registration System)

Um novo serviço de e-mail "Berlandesk" será aberto. Cada vez que um novo usuário deseja se registrar, ele envia ao sistema uma solicitação com seu nome. 
Se esse nome não existir no banco de dados, ele é inserido, e o usuário recebe a resposta OK. Se o nome já existir, o sistema cria um novo nome anexando números a partir de 1 (nome1, nome2, ...) e insere no banco de dados.

Entrada:
A primeira linha contém o número n. As seguintes n linhas contêm as solicitações.

Saída:
Imprima n linhas, que são as respostas do sistema: OK em caso de sucesso, ou um prompt com um novo nome, se o solicitado já estiver ocupado.
*/

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    map<string, int> db;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (db.count(s) == 0) {
            cout << "OK\n";
            db[s] = 1;
        } else {
            cout << s << db[s] << "\n";
            db[s]++;
        }
    }

    return 0;
}
/*
Problema: K - Chessboard and Queens (CSES - 1624)

Sua tarefa é colocar oito rainhas em um tabuleiro de xadrez de modo que nenhuma rainha ataque a outra. Como um desafio adicional, cada quadrado está livre ou reservado, e você só pode colocar rainhas nos quadrados livres. No entanto, os quadrados reservados não impedem que as rainhas ataquem umas às outras. 

Quantas maneiras possíveis existem de colocar as rainhas?

Entrada
A entrada possui oito linhas, e cada uma delas possui oito caracteres. Cada quadrado é livre (.) ou reservado (*).

Saída
Imprima um inteiro: o número de maneiras que você pode colocar as rainhas.
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> board(8);
bool col_taken[8] = {false};
bool diag1[15] = {false};
bool diag2[15] = {false};
int ways = 0;

void solve(int row) {
    if (row == 8) {
        ways++;
        return;
    }

    for (int col = 0; col < 8; col++) {
        if (board[row][col] == '.') {
            if (!col_taken[col] && !diag1[row - col + 7] && !diag2[row + col]) {
                col_taken[col] = diag1[row - col + 7] = diag2[row + col] = true;
                
                solve(row + 1);
                
                col_taken[col] = diag1[row - col + 7] = diag2[row + col] = false;
            }
        }
    }
}

int main() {
    for (int i = 0; i < 8; i++) {
        cin >> board[i];
    }

    solve(0);

    cout << ways << "\n";

    return 0;
}
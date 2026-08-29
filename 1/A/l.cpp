/*
Problema: L - Watermelon (CodeForces - 4A)

Em um dia quente de verão, Pete e seu amigo Billy decidiram comprar uma melancia. Eles escolheram a maior e mais madura, na opinião deles. Depois disso, a melancia foi pesada e a balança mostrou w quilos. Eles correram para casa, morrendo de sede, e decidiram dividir a fruta, no entanto, enfrentaram um problema difícil.

Pete e Billy são grandes fãs de números pares, é por isso que eles querem dividir a melancia de tal forma que cada uma das duas partes pese um número par de quilos; ao mesmo tempo, não é obrigatório que as partes sejam iguais. Os meninos estão extremamente cansados e querem começar a refeição o mais rápido possível, é por isso que você deve ajudá-los e descobrir se eles podem dividir a melancia da maneira que desejam. Com certeza, cada um deles deve receber uma parte de peso positivo.

Entrada
A primeira (e única) linha de entrada contém o número inteiro w (1 <= w <= 100) — o peso da melancia comprada pelos meninos.

Saída
Imprima YES, se os meninos puderem dividir a melancia em duas partes, cada uma delas pesando um número par de quilos; e NO no caso oposto.
*/
#include <iostream>
using namespace std;

int main() {
    int w;
    if (cin >> w) {
        if (w > 2 && w % 2 == 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
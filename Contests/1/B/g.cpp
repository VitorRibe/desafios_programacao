/*
Problema: G - Bear and Prime 100 (CodeForces - 679A)

Este é um problema interativo. Na seção de saída abaixo você verá informações sobre como liberar o buffer de saída (flush).

O Urso Limak pensa em algum número oculto — um inteiro no intervalo [2, 100]. Sua tarefa é dizer se o número oculto é primo ou composto.

Um inteiro x > 1 é chamado de primo se tiver exatamente dois divisores distintos, 1 e x. Se o inteiro x > 1 não for primo, ele é chamado de composto.

Você pode fazer até 20 perguntas sobre os divisores do número oculto. Em cada pergunta você deve imprimir um inteiro do intervalo [2, 100]. O sistema responderá "yes" (sim) se o seu inteiro for um divisor do número oculto. Caso contrário, a resposta será "no" (não).

Por exemplo, se o número oculto for 14, o sistema responderá "yes" apenas se você imprimir 2, 7 ou 14.

Quando você terminar de fazer as perguntas, imprima "prime" (primo) ou "composite" (composto) e encerre o seu programa.

Você receberá o veredito Wrong Answer se fizer mais de 20 perguntas, ou se imprimir um inteiro fora do intervalo [2, 100]. Também receberá Wrong Answer se a resposta impressa estiver incorreta.

Entrada
Após cada pergunta, você deve ler uma string da entrada. Será "yes" se o inteiro impresso for um divisor do número oculto, e "no" caso contrário.

Saída
Até 20 vezes você pode fazer uma pergunta — imprima um inteiro do intervalo [2, 100] em uma linha. Você tem que imprimir o caractere de fim de linha e liberar a saída (flush). Após liberar, você deve ler uma resposta da entrada.

A qualquer momento você pode imprimir a resposta "prime" ou "composite" (sem as aspas). Depois disso, libere a saída e encerre o programa.
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<int> queries = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 4, 9, 25, 49};
    int yes_count = 0;

    for (int i = 0; i < queries.size(); i++) {
        cout << queries[i] << endl;
        
        string response;
        cin >> response;
        
        if (response == "yes") {
            yes_count++;
        }
    }

    if (yes_count >= 2) {
        cout << "composite" << endl;
    } else {
        cout << "prime" << endl;
    }

    return 0;
}
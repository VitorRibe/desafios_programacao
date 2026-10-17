/*
K - Hora de Saquear Cowavans

Como você sabe, os seres mais inteligentes da Terra são, obviamente, as vacas. Esta conclusão foi alcançada há muito tempo pelos alienígenas marcianos, bem como por várias outras civilizações inteligentes do espaço sideral.

Às vezes, as vacas se reúnem em cowavans. Isso parece ser sazonal. Mas, neste momento, as vacas se tornam passivas e reagem mal a estímulos externos. Um cowavan é um alvo perfeito para o disco voador científico marciano, é hora de abduções em grande escala ou, como dizem os marcianos, saques (raids). Simplificando, um cowavan é um conjunto de vacas em fila.

Se numerarmos todas as vacas no cowavan com inteiros positivos de 1 a n, podemos formalizar o modelo popular de abdução, conhecido como o Saque (a, b)-Cowavan: primeiro eles roubam a vaca número a, depois a número a + b, depois a número a + 2*b e assim por diante, até que o número de uma vaca abduzida exceda n. Durante um saque, as vacas não são renumeradas.

Os alienígenas ficariam felizes em colocar todas as vacas a bordo de sua hospitaleira nave, mas infelizmente, a quantidade de espaço de carga é muito, muito limitada. Os pesquisadores, sabendo a massa de cada vaca no cowavan, fizeram p cenários do saque (a, b). Agora eles querem identificar a seguinte coisa para cada cenário individualmente: qual a massa total de carne pura que irá a bordo da nave. Todos os cenários são independentes, no processo de realização dos cálculos as vacas não estão sendo roubadas.

Entrada:
A primeira linha contém o único inteiro positivo n (1 <= n <= 3 * 10^5) — o número de vacas no cowavan.
A segunda linha contém n inteiros positivos w_i, separados por espaços, onde o i-ésimo número descreve a massa da i-ésima vaca no cowavan (1 <= w_i <= 10^9).
A terceira linha contém o único inteiro positivo p — o número de cenários de saques (a, b) (1 <= p <= 3 * 10^5).
Cada linha seguinte contém os parâmetros inteiros a e b do cenário correspondente (1 <= a, b <= n).

Saída:
Imprima para cada cenário do saque (a, b) a massa total de vacas que pode ser roubada usando apenas este cenário.
*/

#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 300005;
const int BLK = 400;

long long w[MAXN];
long long dp[MAXN];
long long ans[MAXN];

struct QuerySmall {
    int a;
    int id;
};

vector<QuerySmall> small_q[BLK + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    int p;
    cin >> p;

    for (int i = 0; i < p; i++) {
        int a, b;
        cin >> a >> b;
        if (b > BLK) {
            long long sum = 0;
            for (int j = a; j <= n; j += b) {
                sum += w[j];
            }
            ans[i] = sum;
        } else {
            small_q[b].push_back({a, i});
        }
    }

    for (int b = 1; b <= BLK; b++) {
        if (small_q[b].empty()) continue;

        for (int i = n; i >= 1; i--) {
            if (i + b <= n) {
                dp[i] = w[i] + dp[i + b];
            } else {
                dp[i] = w[i];
            }
        }

        for (auto &q : small_q[b]) {
            ans[q.id] = dp[q.a];
        }
    }

    for (int i = 0; i < p; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
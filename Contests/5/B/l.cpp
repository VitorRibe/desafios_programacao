/*
L - Consultas de Array Crescente

Você recebe um array que consiste em n inteiros. Os elementos do array são indexados 1, 2, ..., n.
Você pode modificar o array usando a seguinte operação: escolha um elemento do array e aumente seu valor em um.
Sua tarefa é processar q consultas da forma: quando consideramos um subarranjo da posição a até a posição b, qual é o número mínimo de operações após as quais o subarranjo é crescente?
Um array é crescente se cada elemento for maior ou igual ao elemento anterior.

Entrada:
A primeira linha de entrada tem dois inteiros n e q: o tamanho do array e o número de consultas.
A próxima linha tem n inteiros x_1, x_2, ..., x_n: os conteúdos do array.
Finalmente, existem q linhas que descrevem as consultas. Cada linha tem dois inteiros a e b: a posição inicial e final de um subarranjo.

Saída:
Para cada consulta, imprima o número mínimo de operações.

Restrições:
1 <= n, q <= 2 * 10^5
1 <= x_i <= 10^9
1 <= a <= b <= n
*/

#include <iostream>
#include <vector>

using namespace std;

struct Query {
    int b, id;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<long long> a(n + 1);
    vector<long long> pref_a(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pref_a[i] = pref_a[i - 1] + a[i];
    }

    vector<vector<Query>> queries(n + 1);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        queries[l].push_back({r, i});
    }

    vector<int> stk(n + 2);
    vector<long long> pref_b(n + 2, 0);
    int sz = 0;
    
    vector<long long> ans(q);

    for (int i = n; i >= 1; --i) {
        while (sz > 0 && a[i] >= a[stk[sz]]) {
            sz--;
        }
        
        int nxt = (sz > 0) ? stk[sz] : n + 1;
        sz++;
        stk[sz] = i;
        pref_b[sz] = pref_b[sz - 1] + a[i] * (nxt - i);

        for (const auto& query : queries[i]) {
            int b = query.b;
            int query_id = query.id;

            int low = 1, high = sz, pos = sz;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (stk[mid] <= b) {
                    pos = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            long long full_blocks_sum = pref_b[sz] - pref_b[pos];
            long long partial_block_sum = a[stk[pos]] * (b - stk[pos] + 1);
            long long total_b_sum = full_blocks_sum + partial_block_sum;
            long long original_sum = pref_a[b] - pref_a[i - 1];
            
            ans[query_id] = total_b_sum - original_sum;
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}
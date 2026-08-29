/*
Problema: B - Maximum Subsequence (CodeForces - 888E)

Você recebe um array a consistindo de n inteiros, e adicionalmente um inteiro m. Você tem que escolher alguma sequência de índices b_1, b_2, ..., b_k (1 <= b_1 < b_2 < ... < b_k <= n) de tal forma que o valor de (soma de a_{b_i} de i=1 até k) mod m seja maximizado. A sequência escolhida pode ser vazia.

Imprima o valor máximo possível da soma.

Entrada
A primeira linha contém dois inteiros n e m (1 <= n <= 35, 1 <= m <= 10^9).
A segunda linha contém n inteiros a_1, a_2, ..., a_n (1 <= a_i <= 10^9).

Saída
Imprima o valor máximo possível de (soma de a_{b_i} de i=1 até k) mod m.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void get_subset_sums(const vector<long long>& arr, vector<long long>& res, long long m) {
    int n = arr.size();
    for (int i = 0; i < (1 << n); ++i) {
        long long sum = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                sum = (sum + arr[j]) % m;
            }
        }
        res.push_back(sum);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] %= m;
    }

    int mid = n / 2;
    vector<long long> left_arr(a.begin(), a.begin() + mid);
    vector<long long> right_arr(a.begin() + mid, a.end());

    vector<long long> left_sums, right_sums;
    left_sums.reserve(1 << left_arr.size());
    right_sums.reserve(1 << right_arr.size());

    get_subset_sums(left_arr, left_sums, m);
    get_subset_sums(right_arr, right_sums, m);

    sort(right_sums.begin(), right_sums.end());
    right_sums.erase(unique(right_sums.begin(), right_sums.end()), right_sums.end());

    long long max_sum = 0;

    for (long long l_val : left_sums) {
        long long target = m - 1 - l_val;
        auto it = upper_bound(right_sums.begin(), right_sums.end(), target);
        if (it != right_sums.begin()) {
            --it;
            max_sum = max(max_sum, (l_val + *it) % m);
        }
        max_sum = max(max_sum, (l_val + right_sums.back()) % m);
    }

    cout << max_sum << "\n";

    return 0;
}
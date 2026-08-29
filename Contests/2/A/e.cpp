/*
Problema: A - Meet in the Middle (CSES - 1628)

Você recebe um array de n números. De quantas maneiras você pode escolher um subconjunto dos números com soma x?

Entrada
A primeira linha de entrada tem dois números n e x: o tamanho do array e a soma necessária.
A segunda linha tem n inteiros t_1, t_2, ..., t_n: os números no array.

Saída
Imprima o número de maneiras que você pode criar a soma x.

Restrições
- 1 <= n <= 40
- 1 <= x <= 10^9
- 1 <= t_i <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void get_subset_sums(const vector<long long>& arr, vector<long long>& res) {
    int n = arr.size();
    for (int i = 0; i < (1 << n); ++i) {
        long long sum = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                sum += arr[j];
            }
        }
        res.push_back(sum);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<long long> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    int mid = n / 2;
    vector<long long> left_arr(t.begin(), t.begin() + mid);
    vector<long long> right_arr(t.begin() + mid, t.end());

    vector<long long> left_sums, right_sums;
    left_sums.reserve(1 << left_arr.size());
    right_sums.reserve(1 << right_arr.size());

    get_subset_sums(left_arr, left_sums);
    get_subset_sums(right_arr, right_sums);

    sort(right_sums.begin(), right_sums.end());

    long long ways = 0;
    for (long long sum : left_sums) {
        long long target = x - sum;
        auto bounds = equal_range(right_sums.begin(), right_sums.end(), target);
        ways += distance(bounds.first, bounds.second);
    }

    cout << ways << "\n";

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int LOGK = 35;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    vector<vector<int>> up(LOGK, vector<int>(n));
    vector<vector<long long>> sum_w(LOGK, vector<long long>(n));
    vector<vector<int>> min_w(LOGK, vector<int>(n));

    for (int i = 0; i < n; i++) {
        cin >> up[0][i];
    }

    for (int i = 0; i < n; i++) {
        int w;
        cin >> w;
        sum_w[0][i] = w;
        min_w[0][i] = w;
    }

    for (int j = 1; j < LOGK; j++) {
        for (int i = 0; i < n; i++) {
            int next_node = up[j - 1][i];
            up[j][i] = up[j - 1][next_node];
            sum_w[j][i] = sum_w[j - 1][i] + sum_w[j - 1][next_node];
            min_w[j][i] = min(min_w[j - 1][i], min_w[j - 1][next_node]);
        }
    }

    for (int i = 0; i < n; i++) {
        int curr = i;
        long long total_sum = 0;
        int min_edge = 1e9 + 7;

        for (int j = 0; j < LOGK; j++) {
            if ((k >> j) & 1) {
                total_sum += sum_w[j][curr];
                min_edge = min(min_edge, min_w[j][curr]);
                curr = up[j][curr];
            }
        }

        cout << total_sum << " " << min_edge << "\n";
    }

    return 0;
}
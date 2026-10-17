#include <iostream>
#include <vector>

using namespace std;

const int LOGK = 30;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<vector<int>> up(LOGK, vector<int>(n + 1));

    for (int i = 1; i <= n; i++) {
        cin >> up[0][i];
    }

    for (int j = 1; j < LOGK; j++) {
        for (int i = 1; i <= n; i++) {
            up[j][i] = up[j - 1][up[j - 1][i]];
        }
    }

    while (q--) {
        int x, k;
        cin >> x >> k;

        for (int j = 0; j < LOGK; j++) {
            if ((k >> j) & 1) {
                x = up[j][x];
            }
        }

        cout << x << "\n";
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
int a[MAXN];
vector<int> blocks[500];
int block_size;

// Conta quantos elementos no intervalo de índices [l, r] possuem valor entre [low, high]
int count_between(int l, int r, int low, int high) {
    if (l > r || low > high) return 0;
    int cnt = 0;
    int b_start = l / block_size;
    int b_end = r / block_size;

    if (b_start == b_end) {
        for (int i = l; i <= r; i++) {
            if (a[i] >= low && a[i] <= high) cnt++;
        }
    } else {
        for (int i = l; i < (b_start + 1) * block_size; i++) {
            if (a[i] >= low && a[i] <= high) cnt++;
        }
        for (int b = b_start + 1; b < b_end; b++) {
            auto it2 = upper_bound(blocks[b].begin(), blocks[b].end(), high);
            auto it1 = lower_bound(blocks[b].begin(), blocks[b].end(), low);
            cnt += (it2 - it1);
        }
        for (int i = b_end * block_size; i <= r; i++) {
            if (a[i] >= low && a[i] <= high) cnt++;
        }
    }
    return cnt;
}

// Atualiza o valor no vetor e reordena o bloco correspondente
void update_val(int pos, int old_val, int new_val) {
    int b = pos / block_size;
    auto it = lower_bound(blocks[b].begin(), blocks[b].end(), old_val);
    *it = new_val;
    sort(blocks[b].begin(), blocks[b].end());
    a[pos] = new_val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    block_size = max(1, (int)sqrt(n));
    for (int i = 1; i <= n; i++) {
        a[i] = i;
        blocks[i / block_size].push_back(i);
    }

    long long current_inversions = 0;

    while (q--) {
        int l, r;
        cin >> l >> r;

        if (l == r) {
            cout << current_inversions << "\n";
            continue;
        }

        if (l > r) swap(l, r);

        int val_l = a[l];
        int val_r = a[r];

        if (val_l < val_r) {
            int cnt = count_between(l + 1, r - 1, val_l + 1, val_r - 1);
            current_inversions += 1 + 2LL * cnt;
        } else if (val_l > val_r) {
            int cnt = count_between(l + 1, r - 1, val_r + 1, val_l - 1);
            current_inversions -= 1 + 2LL * cnt;
        }

        update_val(l, val_l, val_r);
        update_val(r, val_r, val_l);

        cout << current_inversions << "\n";
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Query {
    int l, r, id;
    bool operator<(const Query& other) const {
        return r < other.r;
    }
};

const int MAXVAL = 1000005;
int bit[300005];
int n;

void update(int idx, int val) {
    for (; idx <= n; idx += idx & -idx) {
        bit[idx] += val;
    }
}

int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += bit[idx];
    }
    return sum;
}

int last_pos[MAXVAL];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int q;
    cin >> q;
    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end());

    vector<int> ans(q);
    int cur_r = 1;

    for (int i = 0; i < q; i++) {
        while (cur_r <= queries[i].r) {
            int val = a[cur_r];
            if (last_pos[val] != 0) {
                update(last_pos[val], -1);
            }
            update(cur_r, 1);
            last_pos[val] = cur_r;
            cur_r++;
        }
        ans[queries[i].id] = query(queries[i].r) - query(queries[i].l - 1);
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Query {
    int l, r, id, block;
    bool operator<(const Query& other) const {
        if (block != other.block) return block < other.block;
        return (block & 1) ? (r < other.r) : (r > other.r);
    }
};

const int MAXVAL = 1 << 20;
long long cnt[MAXVAL];
long long current_ans = 0;
int k;

inline void add(int val) {
    current_ans += cnt[val ^ k];
    cnt[val]++;
}

inline void remove(int val) {
    cnt[val]--;
    current_ans -= cnt[val ^ k];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m >> k)) return 0;

    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        pref[i] = pref[i - 1] ^ x;
    }

    int block_size = max(1, (int)sqrt(n + 1));
    vector<Query> queries(m);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        queries[i].l = l - 1;
        queries[i].r = r;
        queries[i].id = i;
        queries[i].block = queries[i].l / block_size;
    }

    sort(queries.begin(), queries.end());

    vector<long long> ans(m);
    int cur_l = 0, cur_r = -1;

    for (const auto& q : queries) {
        while (cur_l > q.l) add(pref[--cur_l]);
        while (cur_r < q.r) add(pref[++cur_r]);
        while (cur_l < q.l) remove(pref[cur_l++]);
        while (cur_r > q.r) remove(pref[cur_r--]);
        ans[q.id] = current_ans;
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
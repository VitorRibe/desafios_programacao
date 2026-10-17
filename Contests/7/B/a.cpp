#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Query {
    int l, r, id;
    int block;
    bool operator<(const Query& other) const {
        if (block != other.block) return block < other.block;
        return (block & 1) ? (r < other.r) : (r > other.r);
    }
};

const int MAXA = 1000005;
long long cnt[MAXA];
long long current_ans = 0;

inline void add(long long x) {
    current_ans -= cnt[x] * cnt[x] * x;
    cnt[x]++;
    current_ans += cnt[x] * cnt[x] * x;
}

inline void remove(long long x) {
    current_ans -= cnt[x] * cnt[x] * x;
    cnt[x]--;
    current_ans += cnt[x] * cnt[x] * x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    if (!(cin >> n >> t)) return 0;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int block_size = max(1, (int)sqrt(n));
    vector<Query> queries(t);
    for (int i = 0; i < t; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
        queries[i].block = queries[i].l / block_size;
    }

    sort(queries.begin(), queries.end());

    vector<long long> ans(t);
    int cur_l = 1, cur_r = 0;

    for (const auto& q : queries) {
        while (cur_l > q.l) add(a[--cur_l]);
        while (cur_r < q.r) add(a[++cur_r]);
        while (cur_l < q.l) remove(a[cur_l++]);
        while (cur_r > q.r) remove(a[cur_r--]);
        ans[q.id] = current_ans;
    }

    for (int i = 0; i < t; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
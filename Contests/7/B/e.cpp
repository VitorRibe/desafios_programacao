#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

struct Query {
    int l, r, t, id, bl, br;
    bool operator<(const Query& other) const {
        if (bl != other.bl) return bl < other.bl;
        if (br != other.br) return br < other.br;
        return t < other.t;
    }
};

struct Update {
    int pos, old_val, new_val;
};

const int MAXN = 200005;
int a[MAXN], a_orig[MAXN];
int cnt[MAXN];
int freq_cnt[MAXN];

inline void add(int x) {
    freq_cnt[cnt[x]]--;
    cnt[x]++;
    freq_cnt[cnt[x]]++;
}

inline void remove(int x) {
    freq_cnt[cnt[x]]--;
    cnt[x]--;
    freq_cnt[cnt[x]]++;
}

inline void apply_update(int t, int l, int r, const vector<Update>& updates) {
    int pos = updates[t].pos;
    if (pos >= l && pos <= r) {
        remove(a[pos]);
        a[pos] = updates[t].new_val;
        add(a[pos]);
    } else {
        a[pos] = updates[t].new_val;
    }
}

inline void rollback_update(int t, int l, int r, const vector<Update>& updates) {
    int pos = updates[t].pos;
    if (pos >= l && pos <= r) {
        remove(a[pos]);
        a[pos] = updates[t].old_val;
        add(a[pos]);
    } else {
        a[pos] = updates[t].old_val;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    map<int, int> compress;
    int comp_id = 1;

    vector<int> raw_a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> raw_a[i];
        if (!compress.count(raw_a[i])) compress[raw_a[i]] = comp_id++;
        a[i] = compress[raw_a[i]];
        a_orig[i] = a[i];
    }

    vector<Query> queries;
    vector<Update> updates;
    int block_size = pow(n, 2.0 / 3.0);
    if (block_size < 1) block_size = 1;

    int query_idx = 0;
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            queries.push_back({l, r, (int)updates.size() - 1, query_idx++, l / block_size, r / block_size});
        } else {
            int p, x;
            cin >> p >> x;
            if (!compress.count(x)) compress[x] = comp_id++;
            x = compress[x];
            updates.push_back({p, a_orig[p], x});
            a_orig[p] = x;
        }
    }

    sort(queries.begin(), queries.end());

    vector<int> ans(queries.size());
    int cur_l = 1, cur_r = 0, cur_t = -1;

    for (const auto& q_item : queries) {
        while (cur_t < q_item.t) {
            cur_t++;
            apply_update(cur_t, cur_l, cur_r, updates);
        }
        while (cur_t > q_item.t) {
            rollback_update(cur_t, cur_l, cur_r, updates);
            cur_t--;
        }
        while (cur_l > q_item.l) add(a[--cur_l]);
        while (cur_r < q_item.r) add(a[++cur_r]);
        while (cur_l < q_item.l) remove(a[cur_l++]);
        while (cur_r > q_item.r) remove(a[cur_r--]);

        int mex = 1;
        while (freq_cnt[mex] > 0) mex++;
        ans[q_item.id] = mex;
    }

    for (int res : ans) {
        cout << res << "\n";
    }

    return 0;
}
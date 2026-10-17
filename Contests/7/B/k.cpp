#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> t(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    vector<int> ans(n + 1, 0);
    vector<int> vis(n + 1, 0); 

    for (int i = 1; i <= n; i++) {
        if (ans[i] != 0) continue;

        vector<int> path;
        int curr = i;
        while (vis[curr] == 0 && ans[curr] == 0) {
            vis[curr] = 1;
            path.push_back(curr);
            curr = t[curr];
        }

        if (vis[curr] == 1) {
            int cycle_start = curr;
            vector<int> cycle_nodes;
            vector<int> tail_nodes;
            bool inside_cycle = false;

            for (int u : path) {
                if (u == cycle_start) inside_cycle = true;
                if (inside_cycle) {
                    cycle_nodes.push_back(u);
                } else {
                    tail_nodes.push_back(u);
                }
            }

            int cycle_len = cycle_nodes.size();
            for (int u : cycle_nodes) {
                ans[u] = cycle_len;
            }

            int steps = cycle_len;
            for (int j = (int)tail_nodes.size() - 1; j >= 0; j--) {
                steps++;
                ans[tail_nodes[j]] = steps;
            }
        } else {
            int steps = ans[curr];
            for (int j = (int)path.size() - 1; j >= 0; j--) {
                steps++;
                ans[path[j]] = steps;
            }
        }

        for (int u : path) {
            vis[u] = 2;
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
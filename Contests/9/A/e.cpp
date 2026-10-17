/*
E - Fox And Names

Encontrar uma permutação do alfabeto tal que as n strings dadas fiquem em ordem lexicográfica, ou relatar "Impossible".

Entrada:
n.
n strings de letras minúsculas.

Saída:
A permutação (ex: abcdefghijklmnopqrstuvwxyz) ou "Impossible".
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<string> names(n);
    for (int i = 0; i < n; i++) {
        cin >> names[i];
    }

    vector<vector<int>> adj(26);
    vector<int> in_degree(26, 0);

    for (int i = 0; i < n - 1; i++) {
        string a = names[i];
        string b = names[i + 1];
        
        int len = min(a.length(), b.length());
        bool diff_found = false;
        
        for (int j = 0; j < len; j++) {
            if (a[j] != b[j]) {
                adj[a[j] - 'a'].push_back(b[j] - 'a');
                in_degree[b[j] - 'a']++;
                diff_found = true;
                break;
            }
        }
        
        if (!diff_found && a.length() > b.length()) {
            cout << "Impossible\n";
            return 0;
        }
    }

    queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    string ans = "";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans += (char)('a' + u);

        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    if (ans.length() == 26) {
        cout << ans << "\n";
    } else {
        cout << "Impossible\n";
    }

    return 0;
}
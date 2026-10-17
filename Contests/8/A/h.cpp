/*
H - Pontuação Máxima (High Score)

n quartos e m túneis (podem ter peso negativo ou positivo). Encontre a pontuação máxima do quarto 1 ao n. Se puder ser infinitamente grande, imprima -1.

Entrada
n, m.
m linhas a, b, x (túnel a -> b com peso x).

Saída
Pontuação máxima ou -1.
*/

#include <iostream>
#include <vector>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int u, v;
    long long w;
};

vector<vector<int>> adj_fwd, adj_rev;
vector<bool> vis_fwd, vis_rev;

void dfs_fwd(int u) {
    vis_fwd[u] = true;
    for (int v : adj_fwd[u]) {
        if (!vis_fwd[v]) dfs_fwd(v);
    }
}

void dfs_rev(int u) {
    vis_rev[u] = true;
    for (int v : adj_rev[u]) {
        if (!vis_rev[v]) dfs_rev(v);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges;
    adj_fwd.resize(n + 1);
    adj_rev.resize(n + 1);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        adj_fwd[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    vis_fwd.assign(n + 1, false);
    dfs_fwd(1);
    
    vis_rev.assign(n + 1, false);
    dfs_rev(n);

    vector<long long> dist(n + 1, -INF);
    dist[1] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (auto e : edges) {
            if (dist[e.u] != -INF && dist[e.u] + e.w > dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    bool infinite = false;
    for (auto e : edges) {
        if (dist[e.u] != -INF && dist[e.u] + e.w > dist[e.v] && vis_fwd[e.v] && vis_rev[e.v]) {
            infinite = true;
            break;
        }
    }

    if (infinite) {
        cout << -1 << "\n";
    } else {
        cout << dist[n] << "\n";
    }

    return 0;
}
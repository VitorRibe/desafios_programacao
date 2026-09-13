/*
G - Envy

Dado um grafo não direcionado com pesos, determine se para um conjunto de consultas, há uma Árvore Geradora Mínima (MST) que contém todas as arestas do subconjunto consultado.

Entrada:
n, m (vértices e arestas).
m linhas com u, v, w.
q (consultas).
q linhas, começando com k_i (tamanho do subconjunto) e k_i índices de arestas.

Saída:
"YES" se existe tal MST, "NO" caso contrário.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w, id;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct QueryEdge {
    int u, v, id;
};

struct DSU {
    vector<int> parent;
    vector<int> rank;
    vector<pair<int, int>> history;

    DSU(int n) {
        parent.resize(n + 1);
        rank.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return find(parent[i]); 
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) swap(root_i, root_j);
            parent[root_j] = root_i;
            if (rank[root_i] == rank[root_j]) {
                rank[root_i]++;
                history.push_back({root_j, -root_i}); 
            } else {
                history.push_back({root_j, root_i}); 
            }
            return true;
        }
        return false;
    }

    void rollback(int checkpoints) {
        while (history.size() > checkpoints) {
            auto op = history.back();
            history.pop_back();
            int child = op.first;
            int p = op.second;
            if (p < 0) {
                p = -p;
                rank[p]--;
            }
            parent[child] = child;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i + 1;
    }

    vector<Edge> sorted_edges = edges;
    sort(sorted_edges.begin(), sorted_edges.end());

    int q;
    cin >> q;
    
    // O peso máximo é 500000, o vetor deve ter tamanho suficiente para suportar o acesso queries[500000]
    vector<vector<pair<int, int>>> queries(500005); 
    vector<bool> ans(q, true);

    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int edge_idx;
            cin >> edge_idx;
            edge_idx--;
            queries[edges[edge_idx].w].push_back({edge_idx, i});
        }
    }

    DSU dsu(n);
    int edge_ptr = 0;

    for (int w = 1; w <= 500000; w++) {
        if (queries[w].empty()) {
            while (edge_ptr < m && sorted_edges[edge_ptr].w == w) {
                dsu.unite(sorted_edges[edge_ptr].u, sorted_edges[edge_ptr].v);
                edge_ptr++;
            }
            continue;
        }

        sort(queries[w].begin(), queries[w].end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });

        int i = 0;
        while (i < queries[w].size()) {
            int j = i;
            int current_query = queries[w][i].second;
            int checkpoints = dsu.history.size();
            bool possible = true;

            while (j < queries[w].size() && queries[w][j].second == current_query) {
                int edge_idx = queries[w][j].first;
                if (!dsu.unite(edges[edge_idx].u, edges[edge_idx].v)) {
                    possible = false;
                }
                j++;
            }
            if (!possible) ans[current_query] = false;
            dsu.rollback(checkpoints);
            i = j;
        }

        while (edge_ptr < m && sorted_edges[edge_ptr].w == w) {
            dsu.unite(sorted_edges[edge_ptr].u, sorted_edges[edge_ptr].v);
            edge_ptr++;
        }
    }
 
    for (int i = 0; i < q; i++) {
        if (ans[i]) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
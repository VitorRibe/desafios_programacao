/*
I - Estendendo o Conjunto de Pontos (Extending Set of Points)

Para um dado conjunto de pontos 2D S, E(S) é obtido adicionando (x2, y2) se (x1, y1), (x1, y2) e (x2, y1) pertencem ao conjunto, repetindo até não ser mais possível.
Sua tarefa é processar q consultas de adicionar ou remover pontos de S e, após cada consulta, imprimir o tamanho de E(S).

Entrada:
A primeira linha contém q (1 <= q <= 3 * 10^5).
As q linhas seguintes contêm x_i, y_i. Se o ponto já está em S, remova-o. Caso contrário, adicione-o.

Saída:
q inteiros, o tamanho de E(S) após cada consulta.
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MAX_VAL = 300005;
const int MAX_NODES = 600010;

int parent_node[MAX_NODES];
int sz_x[MAX_NODES];
int sz_y[MAX_NODES];
int rank_node[MAX_NODES];
long long current_ans = 0;

struct Op {
    int v, u;
    bool rank_changed;
};

vector<Op> history;
vector<pair<int, int>> seg_tree[4 * MAX_VAL];
long long ans[MAX_VAL];

int find_set(int i) {
    if (parent_node[i] == i) return i;
    return find_set(parent_node[i]); // Sem compressão de caminho para permitir o rollback
}

void unite(int u, int v) {
    int root_u = find_set(u);
    int root_v = find_set(v);
    
    if (root_u == root_v) return;

    if (rank_node[root_u] < rank_node[root_v]) {
        swap(root_u, root_v);
    }

    bool rank_changed = (rank_node[root_u] == rank_node[root_v]);
    history.push_back({root_v, root_u, rank_changed});

    current_ans -= 1LL * sz_x[root_u] * sz_y[root_u];
    current_ans -= 1LL * sz_x[root_v] * sz_y[root_v];

    parent_node[root_v] = root_u;
    sz_x[root_u] += sz_x[root_v];
    sz_y[root_u] += sz_y[root_v];
    
    if (rank_changed) {
        rank_node[root_u]++;
    }

    current_ans += 1LL * sz_x[root_u] * sz_y[root_u];
}

void rollback(int checkpoints) {
    while (history.size() > (size_t)checkpoints) {
        Op op = history.back();
        history.pop_back();
        
        int v = op.v;
        int u = op.u;

        current_ans -= 1LL * sz_x[u] * sz_y[u];

        parent_node[v] = v;
        sz_x[u] -= sz_x[v];
        sz_y[u] -= sz_y[v];
        
        if (op.rank_changed) {
            rank_node[u]--;
        }

        current_ans += 1LL * sz_x[u] * sz_y[u];
        current_ans += 1LL * sz_x[v] * sz_y[v];
    }
}

void add_edge(int node, int l, int r, int ql, int qr, pair<int, int> edge) {
    if (ql <= l && r <= qr) {
        seg_tree[node].push_back(edge);
        return;
    }
    int mid = l + (r - l) / 2;
    if (ql <= mid) add_edge(2 * node, l, mid, ql, qr, edge);
    if (qr > mid) add_edge(2 * node + 1, mid + 1, r, ql, qr, edge);
}

void solve(int node, int l, int r) {
    int checkpoints = history.size();
    
    for (size_t i = 0; i < seg_tree[node].size(); i++) {
        unite(seg_tree[node][i].first, seg_tree[node][i].second);
    }

    if (l == r) {
        ans[l] = current_ans;
    } else {
        int mid = l + (r - l) / 2;
        solve(2 * node, l, mid);
        solve(2 * node + 1, mid + 1, r);
    }

    rollback(checkpoints);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> q)) return 0;

    for (int i = 1; i < MAX_NODES; i++) {
        parent_node[i] = i;
        rank_node[i] = 0;
        if (i <= MAX_VAL) {
            sz_x[i] = 1;
            sz_y[i] = 0;
        } else {
            sz_x[i] = 0;
            sz_y[i] = 1;
        }
    }

    map<pair<int, int>, int> active_points;

    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        
        pair<int, int> pt = {x, y};
        
        if (active_points.count(pt)) {
            add_edge(1, 1, q, active_points[pt], i - 1, {x, y + MAX_VAL});
            active_points.erase(pt);
        } else {
            active_points[pt] = i;
        }
    }

    map<pair<int, int>, int>::iterator it;
    for (it = active_points.begin(); it != active_points.end(); ++it) {
        add_edge(1, 1, q, it->second, q, {it->first.first, it->first.second + MAX_VAL});
    }

    solve(1, 1, q);

    for (int i = 1; i <= q; i++) {
        cout << ans[i] << (i == q ? "" : " ");
    }
    cout << "\n";

    return 0;
}
/*
G - Civilização

O jogo tem n cidades e m estradas bidirecionais (formando florestas). Duas consultas:
1 x: Encontrar o comprimento do caminho mais longo (diâmetro) na região da cidade x.
2 x y: Fundir a região de x com a região de y, adicionando uma estrada que minimize o novo caminho mais longo resultante.

Entrada:
A primeira linha contém n, m, q. 
As próximas m linhas descrevem as estradas.
As próximas q linhas contém as consultas 1 x ou 2 x y.

Saída:
Para cada evento do primeiro tipo imprima a resposta em uma linha separada.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 300005;
vector<int> adj[MAXN];
int parent_node[MAXN], diam[MAXN];
bool visited[MAXN];

int find_set(int v) {
    if (v == parent_node[v])
        return v;
    return parent_node[v] = find_set(parent_node[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        parent_node[b] = a;
        diam[a] = max({diam[a], diam[b], (diam[a] + 1) / 2 + (diam[b] + 1) / 2 + 1});
    }
}

int bfs(int start, int& furthest, vector<int>& comp) {
    queue<int> q;
    vector<int> dist(MAXN, -1);
    
    q.push(start);
    dist[start] = 0;
    visited[start] = true;
    furthest = start;
    comp.push_back(start);
    
    int max_d = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dist[u] > max_d) {
            max_d = dist[u];
            furthest = u;
        }
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                visited[v] = true;
                q.push(v);
                comp.push_back(v);
            }
        }
    }
    return max_d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    for (int i = 1; i <= n; i++) {
        parent_node[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        int root_u = find_set(u);
        int root_v = find_set(v);
        if(root_u != root_v) parent_node[root_v] = root_u;
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            int root = find_set(i);
            int furthest1, furthest2;
            vector<int> comp1, comp2;
            bfs(i, furthest1, comp1);
            
            for(int v : comp1) visited[v] = false;
            
            int d = bfs(furthest1, furthest2, comp2);
            diam[root] = d;
        }
    }

    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x;
            cout << diam[find_set(x)] << "\n";
        } else {
            int x, y;
            cin >> x >> y;
            union_sets(x, y);
        }
    }

    return 0;
}
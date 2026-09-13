/*
E - Você pode responder a estas consultas VI

Dada uma sequência A de N inteiros, você deve aplicar Q operações:
Inserir, deletar, substituir um elemento, e encontrar a soma contígua máxima (não vazia) em um dado intervalo.

Entrada:
A primeira linha contém N.
A linha seguinte contém N inteiros, a sequência inicial A1..AN.
A terceira linha contém Q. As próximas Q linhas contêm as operações:
- I x y: inserir o elemento y na posição x.
- D x: deletar o elemento na posição x.
- R x y: substituir o elemento na posição x por y.
- Q x y: imprimir a soma máxima de A_i + ... + A_j para x <= i <= j <= y.

Saída:
Para cada operação "Q", imprima um inteiro como descrito.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e16;

struct Node {
    long long val;
    int priority;
    int sz;
    long long sum;
    long long max_pref;
    long long max_suff;
    long long max_sub;
    Node *l, *r;
};

int sz(Node* t) {
    return t ? t->sz : 0;
}

long long sum(Node* t) {
    return t ? t->sum : 0;
}

void upd_sz(Node* t) {
    if (t) {
        t->sz = 1 + sz(t->l) + sz(t->r);
        t->sum = t->val + sum(t->l) + sum(t->r);
        
        long long mx_pr = -INF, mx_sf = -INF, mx_sb = -INF;
        long long v = t->val;

        if (t->l) {
            mx_pr = max(t->l->max_pref, t->l->sum + v);
            if (t->r) mx_pr = max(mx_pr, t->l->sum + v + max(0LL, t->r->max_pref));
        } else {
            mx_pr = v;
            if (t->r) mx_pr = max(mx_pr, v + max(0LL, t->r->max_pref));
        }

        if (t->r) {
            mx_sf = max(t->r->max_suff, t->r->sum + v);
            if (t->l) mx_sf = max(mx_sf, t->r->sum + v + max(0LL, t->l->max_suff));
        } else {
            mx_sf = v;
            if (t->l) mx_sf = max(mx_sf, v + max(0LL, t->l->max_suff));
        }

        mx_sb = v;
        if (t->l) mx_sb = max({mx_sb, t->l->max_sub, t->l->max_suff + v});
        if (t->r) mx_sb = max({mx_sb, t->r->max_sub, v + t->r->max_pref});
        if (t->l && t->r) mx_sb = max(mx_sb, t->l->max_suff + v + t->r->max_pref);

        t->max_pref = mx_pr;
        t->max_suff = mx_sf;
        t->max_sub = mx_sb;
    }
}

void split(Node* t, Node*& l, Node*& r, int pos, int add = 0) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    int curr_pos = add + sz(t->l);
    if (curr_pos < pos) {
        split(t->r, t->r, r, pos, curr_pos + 1);
        l = t;
    } else {
        split(t->l, l, t->l, pos, add);
        r = t;
    }
    upd_sz(t);
}

void merge(Node*& t, Node* l, Node* r) {
    if (!l || !r) {
        t = l ? l : r;
    } else if (l->priority > r->priority) {
        merge(l->r, l->r, r);
        t = l;
    } else {
        merge(r->l, l, r->l);
        t = r;
    }
    upd_sz(t);
}

uint32_t xor128() {
    static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    uint32_t t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        Node* new_node = new Node{a, (int)xor128(), 1, a, a, a, a, nullptr, nullptr};
        merge(root, root, new_node);
    }

    int q;
    if (!(cin >> q)) return 0;

    while (q--) {
        char type;
        cin >> type;
        
        if (type == 'I') {
            int x;
            long long y;
            cin >> x >> y;
            x--;
            Node *A, *B;
            split(root, A, B, x);
            Node* new_node = new Node{y, (int)xor128(), 1, y, y, y, y, nullptr, nullptr};
            merge(root, A, new_node);
            merge(root, root, B);
        } else if (type == 'D') {
            int x;
            cin >> x;
            x--;
            Node *A, *B, *C;
            split(root, A, B, x);
            split(B, B, C, 1);
            merge(root, A, C);
        } else if (type == 'R') {
            int x;
            long long y;
            cin >> x >> y;
            x--;
            Node *A, *B, *C;
            split(root, A, B, x);
            split(B, B, C, 1);
            if (B) {
                B->val = y;
                upd_sz(B);
            }
            merge(root, A, B);
            merge(root, root, C);
        } else if (type == 'Q') {
            int x, y;
            cin >> x >> y;
            x--;
            Node *A, *B, *C;
            split(root, A, B, x);
            split(B, B, C, y - x);
            if (B) {
                cout << B->max_sub << "\n";
            }
            merge(root, A, B);
            merge(root, root, C);
        }
    }

    return 0;
}
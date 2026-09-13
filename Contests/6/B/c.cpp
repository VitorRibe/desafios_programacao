/*
C - Soma de Intervalo e Reversão de Intervalo

Você recebe uma sequência a_0, a_1, ..., a_{N-1} consistindo de N inteiros.
Processe Q consultas dos seguintes tipos em ordem:
0 l r: Reverta a_l, a_{l+1}, ..., a_{r-1}.
1 l r: Imprima a soma de a_i do índice l até r-1.

Restrições:
0 <= N <= 2 * 10^5
0 <= Q <= 2 * 10^5
0 <= a_i <= 10^9
0 <= l_j <= r_j <= N
*/

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    long long val;
    int priority;
    int sz;
    long long sum;
    bool rev;
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
    }
}

void push(Node* t) {
    if (t && t->rev) {
        t->rev = false;
        swap(t->l, t->r);
        if (t->l) t->l->rev ^= true;
        if (t->r) t->r->rev ^= true;
    }
}

void split(Node* t, Node*& l, Node*& r, int pos, int add = 0) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    push(t);
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
    push(l);
    push(r);
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

// Pseudo-random generator replacement
uint32_t xor128() {
    static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    uint32_t t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    Node* root = nullptr;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        Node* new_node = new Node{a, (int)xor128(), 1, a, false, nullptr, nullptr};
        merge(root, root, new_node);
    }

    while (q--) {
        int type, l, r;
        cin >> type >> l >> r;
        
        Node *A, *B, *C;
        split(root, A, B, l);
        split(B, B, C, r - l);
        
        if (type == 0) {
            if (B) B->rev ^= true;
        } else {
            cout << sum(B) << "\n";
        }
        
        merge(root, A, B);
        merge(root, root, C);
    }

    return 0;
}
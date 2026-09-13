/*
D - Camisetas

Uma grande remessa de camisetas vai à venda. Em todos os n tipos de camisetas, a camiseta do i-ésimo tipo tem preço c_i e qualidade q_i.
k clientes virão à loja, o j-ésimo cliente estará pronto para gastar até b_j na compra de camisetas.
Todos os clientes desejam comprar o maior número possível de camisetas da mais alta qualidade e, em caso de empate, comprarão a mais barata.
Eles não comprarão mais de uma camiseta de um mesmo tipo.
Determine o número de camisetas que cada cliente comprará.

Entrada:
A primeira linha contém n (1 <= n <= 2 * 10^5) — o número de tipos de camisetas.
As n linhas seguintes contêm c_i e q_i (1 <= c_i, q_i <= 10^9).
A linha seguinte contém k (1 <= k <= 2 * 10^5).
A linha seguinte contém k inteiros b_1, b_2, ..., b_k (1 <= b_j <= 10^9).

Saída:
Imprima k inteiros indicando a quantidade de camisetas compradas por cada cliente.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Shirt {
    int c, q;
    bool operator<(const Shirt& other) const {
        if (q != other.q) return q > other.q;
        return c < other.c;
    }
};

struct Node {
    int id;
    long long b;
    int ans;
    long long lazy_b;
    int lazy_ans;
    int priority;
    Node *l, *r;
};

void push(Node* t) {
    if (t && (t->lazy_b || t->lazy_ans)) {
        if (t->l) {
            t->l->b += t->lazy_b;
            t->l->ans += t->lazy_ans;
            t->l->lazy_b += t->lazy_b;
            t->l->lazy_ans += t->lazy_ans;
        }
        if (t->r) {
            t->r->b += t->lazy_b;
            t->r->ans += t->lazy_ans;
            t->r->lazy_b += t->lazy_b;
            t->r->lazy_ans += t->lazy_ans;
        }
        t->lazy_b = 0;
        t->lazy_ans = 0;
    }
}

void split(Node* t, long long key, Node*& l, Node*& r) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    push(t);
    if (t->b < key) {
        split(t->r, key, t->r, r);
        l = t;
    } else {
        split(t->l, key, l, t->l);
        r = t;
    }
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
}

void insert_node(Node*& t, Node* it) {
    if (!t) {
        t = it;
        return;
    }
    push(t);
    if (it->priority > t->priority) {
        split(t, it->b, it->l, it->r);
        t = it;
    } else {
        if (it->b < t->b) {
            insert_node(t->l, it);
        } else {
            insert_node(t->r, it);
        }
    }
}

uint32_t xor128() {
    static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    uint32_t t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}

vector<int> final_ans;

void store_answers(Node* t) {
    if (!t) return;
    push(t);
    final_ans[t->id] = t->ans;
    store_answers(t->l);
    store_answers(t->r);
}

void extract_and_reinsert(Node* t, Node*& root) {
    if (!t) return;
    push(t);
    extract_and_reinsert(t->l, root);
    extract_and_reinsert(t->r, root);
    t->l = t->r = nullptr;
    insert_node(root, t);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Shirt> shirts(n);
    for (int i = 0; i < n; i++) {
        cin >> shirts[i].c >> shirts[i].q;
    }
    sort(shirts.begin(), shirts.end());

    int k;
    cin >> k;
    final_ans.resize(k);
    Node* root = nullptr;

    for (int i = 0; i < k; i++) {
        long long b;
        cin >> b;
        Node* new_node = new Node{i, b, 0, 0, 0, (int)xor128(), nullptr, nullptr};
        insert_node(root, new_node);
    }

    for (int i = 0; i < n; i++) {
        long long c = shirts[i].c;
        Node *A, *B, *C;
        split(root, c, A, B);
        split(B, 2 * c, B, C);

        if (C) {
            C->b -= c;
            C->ans += 1;
            C->lazy_b -= c;
            C->lazy_ans += 1;
        }

        if (B) {
            B->b -= c;
            B->ans += 1;
            B->lazy_b -= c;
            B->lazy_ans += 1;
            extract_and_reinsert(B, A);
        }

        merge(root, A, C);
    }

    store_answers(root);

    for (int i = 0; i < k; i++) {
        cout << final_ans[i] << (i == k - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
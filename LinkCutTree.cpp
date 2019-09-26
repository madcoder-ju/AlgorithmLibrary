/*
 * Perform Q queries of following types
 *  link u v: add an edge from v to u
 *  cut v: cut the edge parent[ v ] to v
 *  lca u v: print lca of u and v
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 1;

struct Node {
    int sz, label;
    bool flip;
    Node *p, *pp, *l, *r;
    Node() : p(0), pp(0), l(0), r(0), flip(false) {}
};

void update(Node *x) {
    x->sz = 1;
    if( x->l )
        x->sz += x->l->sz;
    if( x->r )
        x->sz += x->r->sz;
}
void propagate(Node *x) {
    if( x-> flip ) {
        if( x->l ) {
            x->l->flip ^= 1;
            swap(x->l->l, x->l->r);
        }
        if( x->r ) {
            x->r->flip ^= 1;
            swap(x->r->l, x->r->r);
        }
        x->flip = 0;
    }
}
void rotateLeft(Node *x) {
    Node *y = x->p, *z = y->p;
    propagate(y);
    propagate(x);
    if((y->r = x->l))
        y->r->p = y;
    x->l = y, y->p = x;
    if((x->p = z)) {
        if(y == z->l)
            z->l = x;
        else
            z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
}
void rotateRight(Node *x) {
    Node *y = x->p, *z = y->p;
    propagate(y);
    propagate(x);
    if((y->l = x->r))
        y->l->p = y;
    x->r = y, y->p = x;
    if((x->p = z)) {
        if(y == z->l)
            z->l = x;
        else
            z->r = x;
    }
    x->pp = y->pp;
    y->pp = 0;
    update(y);
}
void splay(Node *x) {
    Node *y, *z;
    while(x->p) {
        y = x->p;
        if(y->p == 0) {
            if(x == y->l)
                rotateRight(x);
            else
                rotateLeft(x);
        } else {
            z = y->p;
            if(y == z->l) {
                if(x == y->l)
                    rotateRight(y), rotateRight(x);
                else
                    rotateLeft(x), rotateRight(x);
            } else {
                if(x == y->r)
                    rotateLeft(y), rotateLeft(x);
                else
                    rotateRight(x), rotateLeft(x);
            }
        }
    }
    propagate(x);
    update(x);
}

Node *access(Node *x) {
    splay(x);
    if(x->r) {
        x->r->pp = x;
        x->r->p = 0;
        x->r = 0;
        update(x);
    }

    Node *last = x;
    while(x->pp) {
        Node *y = x->pp;
        last = y;
        splay(y);
        if(y->r) {
            y->r->pp = y;
            y->r->p = 0;
        }
        y->r = x;
        x->p = y;
        x->pp = 0;
        update(y);
        splay(x);
    }
    return last;
}
Node *root(Node *x) {
    access(x);
    while(x->l)
        x = x->l;
    splay(x);
    return x;
}

void cut(Node *x) {
    access(x);
    x->l->p = 0;
    x->l = 0;
    update(x);
}

void link(Node *x, Node *y) {
    access(x);
    access(y);
    x->l = y;
    y->p = x;
    update(x);
}

Node *lca(Node *x, Node *y) {
    access(x);
    return access(y);
}

int depth(Node *x) {
    access(x);
    return x->sz - 1;
}

void make_root(Node *x) {
    access(x);
    x->flip = true;
    swap(x->l, x->r);
}
class LinkCut {
    Node *x;

public:
    LinkCut(int n) {
        x = new Node[n + 1];
        for(int i = 1; i <= n; i++) {
            x[i].label = i;
            update(&x[i]);
        }
    }

    virtual ~LinkCut() {
        delete[] x;
    }
    
    // make_root(int u): makes u the root of it's auxilary tree
    void make_root(int u) {
        return ::make_root(&x[u]);
    }

    // link(u, v): adds an directed edge u to v
    void link(int u, int v) {
        ::make_root(&x[v]);
        ::link(&x[v], &x[u]);
    }

    // cut(u, v): cuts the edge from u to v
    void cut(int u, int v) {
        if( depth(u) > depth(v) ) ::cut(&x[u]);
        else ::cut( &x[v] );
    }

    // root(u): the current root of u in the original tree
    int root(int u) {
        return ::root(&x[u])->label;
    }

    // depth(u): the depth of u in the original tree
    int depth(int u) {
        return ::depth(&x[u]);
    }

    // lca(u, v): lca of u and v in the current tree of u and v
    int lca(int u, int v) {
        return ::lca(&x[u], &x[v])->label;
    }

} ;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    int n, q;
    cin >> n >> q;

    LinkCut lct(n);

    while( q-- ) {
        string op;
        cin >> op;
        if( op == "add" ) {
            int u, v;
            cin >> u >> v;
            lct.link(u, v);
        } else if( op == "rem" ) {
            int u, v;
            cin >> u >> v;
            lct.cut(u, v);
        } else {
            int u, v;
            cin >> u >> v;
            if( lct.root(u) == lct.root(v) ) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}

//  SPOJ OTOCI: OTOCI
//  link cut tree + point update + path query
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll N = 3e4 + 34;
ll parent[ N ], a[ N ];

struct Node {
    ll sz, label;
    ll data, res, lazy;
    Node *p, *pp, *l, *r;
    Node() {
        sz = label = data = res = lazy = 0;
        p = pp = l = r = 0;
    }
};

void update(Node *x) {
    x->sz = 1;
    x->res = x->data;
    if( x->l )
        x->sz += x->l->sz,
        x->res += x->l->res;
    if( x->r )
        x->sz += x->r->sz,
        x->res += x->r->res;
}
void propagate(Node *x) {
    if( x-> lazy ) {
        if( x->l ) {
            x->l->lazy ^= 1;
            swap(x->l->l, x->l->r);
        }
        if( x->r ) {
            x->r->lazy ^= 1;
            swap(x->r->l, x->r->r);
        }
        x->lazy = 0;
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

ll depth(Node *x) {
    access(x);
    return x->sz - 1;
}

void set_value(Node *x, ll v) {
    access(x);
    x->data = v;
    update(x);
}

void make_root(Node *x) {
    access(x);
    x->lazy = 1;
    swap(x->l, x->r);
}
class LinkCut {
    Node *x;

public:
    LinkCut(ll n) {
        x = new Node[n + 1];
        for(ll i = 1; i <= n; i++) {
            x[i].label = i;
            update(&x[i]);
        }
    }

    virtual ~LinkCut() {
        delete[] x;
    }

    void make_root(ll u) {
        return ::make_root(&x[u]);
    }

    // link(u, v): adds an directed edge u to v
    void link(ll u, ll v) {
        ::make_root(&x[u]);
        ::link(&x[u], &x[v]);
    }

    void set_value(ll u, ll v) {
        ::set_value(&x[u], v);
    }

    //cut(u, v): cuts the edge u to v
    void cut(ll u, ll v) {
        if( depth(u) > depth(v) )
            ::cut(&x[u]);
        else ::cut( &x[v] );
    }

    // cut(u): cuts the edge from parent of u to u and makes two rooted trees
    // one's root is previous root and other's root is u
    void cut(ll u) {
        ::cut(&x[u]);
    }

    // root(u): the current root of u in the original tree
    ll root(ll u) {
        return ::root(&x[u])->label;
    }

    // depth(u): the depth of u in the original tree
    ll depth(ll u) {
        return ::depth(&x[u]);
    }

    // lca(u, v): lca of u and v in the current tree of u and v
    ll lca(ll u, ll v) {
        return ::lca(&x[u], &x[v])->label;
    }

    ll path(ll u) {
        ::access(&x[u]);
        return x[u].res;
    }

} *tree;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);



    ll n, q;
    cin >> n;

    tree = new LinkCut(n);
    for(ll i = 1; i <= n; i += 1) {
        cin >> a[ i ];
        tree->set_value(i, a[ i ]);
    }
    cin >> q;

    ll u, v;
    while( q-- ) {
        string op;
        cin >> op;
        if( op[ 0 ] == 'b' ) {
            cin >> u >> v;
            if( tree->root(u) == tree->root(v) ) cout << "no\n";
            else {
                cout << "yes\n";
                tree->link(u, v);
            }
        } else if( op[ 0 ] == 'p'){
            cin >> u >> v;
            tree->set_value(u, v);
        } else {
            cin >> u >> v;
            if( tree->root(u) != tree->root(v) ) cout << "impossible\n";
            else {
                tree->make_root(u);
                cout << tree->path(v) << "\n";
            }
        }
    }

    return 0;
}

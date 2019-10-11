#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 15, LOG = 20;

struct Persistent {
    int l, r, s;
    Persistent() { l = r = s = 0; }
} t[ N << 5 ];

vector<int> g[ N ];
int n, avail, d[ N ], a[ N ], p[ N ][ LOG ], root[ N << 5 ];
map<int,int> vis;

int update(int pre, int b, int e, int pos) {
    int node = ++avail;
    t[ node ] = t[ pre ];
    if( b == e ) {
        t[ node ].s += 1;
        return node;
    }
    int m = (b + e) >> 1;
    if( pos <= m ) t[ node ].l = update(t[ node ].l, b, m, pos);
    else t[ node ].r = update(t[ node ].r, m + 1, e, pos);
    t[ node ].s = t[ t[ node ].l ].s + t[ t[ node ].r ].s;
    return node;
}
int query(int u, int v, int lca, int lcaPar, int b, int e, int k) {
    if( b == e ) {
        return b;
    }
    int m = (b + e) >> 1;
    int c = t[ t[ u ].l ].s + t[ t[ v ].l ].s
            - t[ t[ lca ].l ].s - t[ t[ lcaPar ].l ].s;
    if( c >= k ) return query(t[ u ].l, t[ v ].l, t[ lca ].l, t[ lcaPar ].l, b, m, k);
    return query(t[ u ].r, t[ v ].r, t[ lca ].r, t[ lcaPar ].r, m + 1, e, k - c);
}

void dfs(int u = 1, int par = 0) {
    root[ u ] = update(root[ par ], 1, n, vis[ a[ u ] ]);
    d[ u ] = d[ par ] + 1;
    p[ u ][ 0 ] = par;
    for(int i = 1; i < LOG; i += 1)
        p[ u ][ i ] = p[ p[ u ][ i - 1 ] ][ i - 1 ];
    for(int v : g[ u ]) {
        if( v == par ) continue;
        dfs(v, u);
    }
}
int getLCA(int u, int v) {
    if( d[ u ] < d[ v ] ) swap(u, v);
    for(int i = LOG - 1; ~i; i -= 1)
        if( d[ p[ u ][ i ] ] >= d[ v ])
            u = p[ u ][ i ];
    if( v == u ) return u;
    for(int i = LOG - 1; ~i; i -= 1)
        if( p[ u ][ i ] != p[ v ][ i ] )
            u = p[ u ][ i ], v = p[ v ][ i ];
    return p[ u ][ 0 ];
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m;
    cin >> n >> m;
    vector<int> vec;
    for(int i = 1; i <= n; i += 1) {
        cin >> a[ i ];
        vec.push_back(a[ i ]);
    }
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    for(int i = 1; i < n; i += 1) {
        int u, v;
        cin >> u >> v;
        g[ u ].push_back(v);
        g[ v ].push_back(u);
    }
    n = 0;
    for(int &x : vec)
        vis[ x ] = ++n;
    dfs();
    while( m-- ) {
        int u, v, k;
        cin >> u >> v >> k;
        int lca = getLCA(u, v);
        cout << vec[ query(root[ u ], root[ v ], root[ lca ], root[ p[ lca ][ 0 ] ], 1, n, k) - 1 ] << '\n';
    }
    return 0;
}

//  CodeChef DISTNUM3
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 25, LOG = 20, squareRoot = 2300;

map<int,int> v;
vector<int> g[ N ];
int n, m, t, no, last[ N ], vis[ N ], st[ N ], res[ N ], en[ N ], c[ N ];
int ans, f[ N ], nodeAt[ N ], p[ N ][ LOG ], d[ N ];

struct Query {
    int l, r, t, qno, lbox, rbox, lca;
    bool operator < (const Query& q) const {
        if( lbox == q.lbox ) {
            if( rbox == q.rbox )
                return (rbox & 1) ? t > q.t : t < q.t;
            return rbox < q.rbox;
        }
        return lbox < q.lbox;
    }
} q[ N ];
struct Update {
    int v, x, pre;
} pe[ N ];

void dfs(int u = 1, int par = 0) {
    d[ u ] = d[ par ] + 1;
    p[ u ][ 0 ] = par;
    for(int i = 1; i < LOG; i += 1)
        p[ u ][ i ] = p[ p[ u ][ i - 1 ] ][ i - 1 ];
    st[ u ] = ++t;
    nodeAt[ t ] = u;
    for(int v : g[ u ]) {
        if( v == par ) continue;
        dfs(v, u);
    }
    en[ u ] = ++t;
    nodeAt[ t ] = u;
}
int getLCA(int u, int v) {
    if( d[ u ] < d[ v ] ) swap(u, v);
    for(int i = LOG - 1; ~i; i -= 1)
        if( d[ p[ u ][ i ] ] >= d[ v ] )
            u = p[ u ][ i ];
    if( v == u ) return u;
    for(int i = LOG - 1; ~i; i -= 1)
        if( p[ u ][ i ] != p[ v ][ i ] )
            u = p[ u ][ i ],
            v = p[ v ][ i ];
    return p[ u ][ 0 ];
}
int squeeze(int x) {
    if( v.find(x) == v.end() )
        v[ x ] = ++no;
    return v[ x ];
}
void inc(int x) {
    f[ x ] += 1;
    if( f[ x ] == 1 ) ans += 1;
}
void dec(int x) {
    f[ x ] -= 1;
    if( f[ x ] == 0 ) ans -= 1;
}
void update(int u) {
    int x = c[ u ];
    if( vis[ u ] == 0 ) inc(x);
    else dec(x);
    vis[ u ] ^= 1;
}
void addt(int t) {
    int v = pe[ t ].v, x = pe[ t ].x;
    if( vis[ v ] ) {
        dec(c[ v ]);
    }
    c[ v ] = x;
    if( vis[ v ] ) {
        inc(c[ v ]);
    }
}
void delt(int t) {
    int v = pe[ t ].v, x = pe[ t ].pre;
    if( vis[ v ] ) {
        dec(c[ v ]);
    }
    c[ v ] = x;
    if( vis[ v ] ) {
        inc(c[ v ]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    for(int i = 1; i <= n; i += 1) {
        cin >> c[ i ];
        c[ i ] = squeeze( c[ i ] );
        last[ i ] = c[ i ];
    }

    for(int i = 1; i < n; i += 1) {
        int u, v;
        cin >> u >> v;
        g[ u ].push_back( v );
        g[ v ].push_back( u );
    }

    dfs();

    int k = 0, l = 0;
    for(int i = 1; i <= m; i += 1) {
        int op;
        cin >> op;
        if( op == 1 ) {
            int u, v;
            cin >> u >> v;

            if( st[ u ] > st[ v ] )
                swap(u, v);

            int lca = getLCA(u, v);
            q[ ++k ].qno = k;
            q[ k ].t = l;

            if( u == lca ) {
                q[ k ].l = st[ u ];
                q[ k ].r = st[ v ];
                q[ k ].lca = 0;
            } else {
                q[ k ].l = en[ u ];
                q[ k ].r = st[ v ];
                q[ k ].lca = lca;
            }
            q[ k ].lbox = q[ k ].l / squareRoot;
            q[ k ].rbox = q[ k ].r / squareRoot;
        } else {
            int v, x;
            cin >> v >> x;
            x = squeeze( x );
            pe[ ++l ].v = v;
            pe[ l ].x = x;
            pe[ l ].pre = last[ v ];
            last[ v ] = x;
        }
    }
    sort(q + 1, q + k + 1);

    l = 1;
    int r = 1;
    t = 0;
    for(int i = 1; i <= k; i += 1) {
        while( q[ i ].t < t ) delt( t-- );
        while( q[ i ].t > t ) addt( ++t );
        while( q[ i ].l < l ) update( nodeAt[ --l ] );
        while( q[ i ].r >= r ) update( nodeAt[ r++ ] );
        while( q[ i ].l > l ) update( nodeAt[ l++ ] );
        while( q[ i ].r + 1 < r ) update( nodeAt[ --r ] );

        if( q[ i ].lca ) {
            update(q[ i ].lca);
        }
        res[ q[ i ].qno ] = ans;
        if( q[ i ].lca ) {
            update(q[ i ].lca);
        }
    }
    for(int i = 1; i <= k; i += 1)
        cout << res[ i ] << '\n';
    return 0;
}

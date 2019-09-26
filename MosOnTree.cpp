// SPOJ COT2
#include <bits/stdc++.h>

using namespace std;

const int N = 40001, LOG = 16;
int n, m, t, a[ N ], d[ N ], st[ N ], en[ N ], vis[ N ], res[ 100001 ], nodeAt[ 300001 ], p[ N ][ LOG ];
vector<int> g[ N ];
unordered_map<int, int> f;

struct Query {

    int l, r, qno, box, lca;

    bool operator < (const Query& q) const {
        if( box == q.box )
            return (box & 1) ? r > q.r : r < q.r;
        return box < q.box;
    }

} q[ 100001 ];

void dfs(int u, int par) {
    st[ u ] = ++t;
    nodeAt[ t ] = u;

    d[ u ] = d[ par ] + 1;
    p[ u ][ 0 ] = par;
    for(int i = 1; i < LOG; i += 1)
        p[ u ][ i ] = p[ p[ u ][ i - 1 ] ][ i - 1 ];

    for(int v : g[ u ]) {
        if( v != par ) {
            dfs(v, u);
        }
    }
    en[ u ] = ++t;
    nodeAt[ t ] = u;
}

int getLCA(int u, int v) {
    if( d[ u ] < d[ v ] ) swap(u, v);
    for(int i = LOG - 1; ~i; i -= 1) {
        if( d[ p[ u ][ i ] ] >= d[ v ] ) u = p[ u ][ i ];
    }
    if( u == v ) return u;
    for(int i = LOG - 1; ~i; i -= 1) {
        if( p[ u ][ i ] != p[ v ][ i ] ) {
            u = p[ u ][ i ];
            v = p[ v ][ i ];
        }
    }
    return p[ u ][ 0 ];
}

int ans;

void inc(int x) {
    f[ a[ x ] ] += 1;
    if( f[ a[ x ] ] == 1 ) ans += 1;
}

void dec(int x) {
    f[ a[ x ] ] -= 1;
    if( f[ a[ x ] ] == 0 ) ans -= 1;
}
void update(int x) {
    if( vis[ x ] ) dec(x);
    else inc(x);
    vis[ x ] ^= 1;
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i += 1) {
        scanf("%d", &a[ i ]);
    }

    int edge = n - 1;
    while( edge-- ) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[ u ].push_back( v );
        g[ v ].push_back( u );
    }

    dfs( 1, 0 );
    int squareRoot = sqrt(t);
    for(int i = 1; i <= m; i += 1) {

        int u, v;
        scanf("%d %d", &u, &v);
        if( st[ u ] > st[ v ] ) swap(u, v);

        int lca = getLCA(u, v);
        q[ i ].qno = i;
        if( lca == u ) {
            q[ i ].l = st[ u ];
            q[ i ].r = st[ v ];
            q[ i ].lca = 0;
        } else {
            q[ i ].l = en[ u ];
            q[ i ].r = st[ v ];
            q[ i ].lca = lca;
        }
        q[ i ].box = q[ i ].l / squareRoot;
    }

    sort(q + 1, q + m + 1);

    int l = 1, r = 1;
    ans = 0;
    for(int i = 1; i <= m; i += 1) {

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
    for(int i = 1; i <= m; i += 1)
        printf("%d\n", res[ i ]);

    return 0;
}

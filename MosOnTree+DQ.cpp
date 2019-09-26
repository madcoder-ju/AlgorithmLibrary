// CodeChef VLB
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const int N = 2e5 + 25, LOG = 20;

struct data {
    int l, r, box, qno, lca;
    bool operator <(const data& q) const {
        if( box == q.box )
            return ( box & 1 ) ? r > q.r : r < q.r;
        return box < q.box;
    }
} q[ N ];

bool vis[N];
vector<int> g[ N ];
deque<int> dq[ 15 ];
int n, t, st[ N ], en[ N ], nodeAt[ N ], d[ N ], p[ N ][ 20 ];
ll ans, res[ N ], sum[ N ], col[ N ], val[ N ];

void dfs(int u = 1, int par = 0) {
    st[ u ] = ++t;
    nodeAt[ t ] = u;
    p[ u ][ 0 ] = par;
    d[ u ] = d[ par ] + 1;
    for(int i = 1; i < LOG; i += 1)
        p[ u ][ i ] = p[ p[ u ][ i - 1 ] ][ i - 1 ];
    for(int v : g[ u ]) {
        if( v == par ) continue;
        dfs(v, u);
    }
    en[ u ] = ++t;
    nodeAt[ t ] = u;
}

int getLCA(int u, int v) {
    if( d[ u ] < d[ v ] )
        swap(u, v);
    for(int i = LOG - 1; ~i; i -= 1) {
        if( d[ p[ u ] [ i ] ] >= d[ v ])
            u = p[ u ][ i ];
    }
    if( v == u ) return u;
    for(int i = LOG - 1; ~i; i -= 1) {
        if( p[ u ][ i ] != p[ v ][ i ] ) {
            u = p[ u ][ i ];
            v = p[ v ][ i ];
        }
    }
    return p[ u ][ 0 ];
}
void add(int u, bool frnt) {
    int c = col[ u ];
    ll h = val[ u ];
    if( vis[ u ] == 0 ) {
        if( !dq[ c ].empty() ) {
            h = ( frnt ? dq[ c ].front(): dq[ c ].back()) - h;
            h *= h;
            sum[ c ] += h;
            ans += h;
        }
        frnt ? dq[ c ].push_front( val[ u ] ) : dq[ c ].push_back( val[ u ] );
    } else {
        if( !dq[ c ].empty()) {
            frnt ? dq[ c ].pop_front(): dq[ c ].pop_back();
        }
        if( !dq[ c ].empty()) {
            h = (frnt ? dq[ c ].front(): dq[ c ].back()) - h;
            h *= h;
            sum[ c ] -= h;
            ans -= h;
        }
    }
    vis[ u ] = !vis[ u ];
}

void rem(int u, bool frnt) {
    int c = col[ u ];
    ll h = val[ u ];
    if(vis[u]) {
        if( !dq[ c ].empty()) {
            frnt ? dq[ c ].pop_front(): dq[ c ].pop_back();
        }
        if( !dq[ c ].empty()) {
            h = (frnt ? dq[ c ].front(): dq[ c ].back()) - h;
            h *= h;
            sum[ c ] -= h;
            ans -= h;
        }
    } else {
        if( !dq[ c ].empty() ) {
            h = ( frnt ? dq[ c ].front(): dq[ c ].back()) - h;
            h *= h;
            sum[ c ] += h;
            ans += h;
        }
        frnt ? dq[ c ].push_front( val[ u ] ) : dq[ c ].push_back( val[ u ] );
    }
    vis[u]=!vis[u];
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n;

    for(int i = 1; i <= n; i += 1) cin >> col[ i ];
    for(int i = 1; i <= n; i += 1) cin >> val[ i ];

    for(int i = 1; i <= n - 1; i += 1) {
        int u, v;
        cin >> u >> v;
        g[ u ].push_back( v );
        g[ v ].push_back( u );
    }

    dfs();

    int m;
    cin >> m;

    int squareRoot = sqrt( t );
    for(int i = 1; i <= m; i += 1) {
        int u, v;
        cin >> u >> v;
        if( st[ v ] < st[ u ] ) swap(u, v);
        int lca = getLCA(u, v);
        if( lca == u ) {
            q[ i ].l = st[ u ];
            q[ i ].r = st[ v ];
        } else {
            q[ i ].l = en[ u ];
            q[ i ].r = st[ v ];
        }
        q[ i ].qno = i;
        q[ i ].lca = lca;
        q[ i ].box = q[ i ].l / squareRoot;
    }

    sort(q + 1, q + m + 1);

    int l = 1, r = 1;
    for(int i = 1; i <= m; i += 1) {

        while( q[ i ].l < l ) add( nodeAt[ --l ], 1 );
        while( q[ i ].r >= r ) add( nodeAt[ r++ ], 0 );
        while( q[ i ].l > l ) rem( nodeAt[ l++ ], 1 );
        while( q[ i ].r + 1 < r ) rem( nodeAt[ --r ], 0 );

        res[ q[ i ].qno ] = ans - sum[ col[ q[ i ].lca ] ];
    }

    for(int i = 1; i <= m; i += 1)
        cout << res[ i ] << '\n';

    return 0;
}

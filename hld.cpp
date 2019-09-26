// Hackerrank: Rooted Tree
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const int N = 1e5 + 1, mod = 1e9 + 7;

ll V;
int n, q, p[ N ], d[ N ], sz[ N ], ara[ N ], big[ N ];
int l, r, K, t, head[ N ], st[ N ], en[ N ];
vector<int> g[ N ];

struct NODE {
    ll l, s, v, k;
} tr[ N << 2 ];

void dfs(int u, int par) {
    p[ u ] = par;
    ll bigson = -1;
    sz[ u ] = 1;
    for(int &v : g[ u ]) {
        if( v == par ) continue;
        d[ v ] = d[ u ] + 1;
        dfs(v, u);
        sz[ u ] += sz[ v ];
        if( bigson == -1 || sz[ v ] > sz[ bigson ] )
            bigson = v;
    }
    big[ u ] = bigson;
}
void HLD(int u, int par) {
    st[ u ] = ++t;
    if( ~big[ u ] ) head[ big[ u ] ] = head[ u ], HLD(big[ u ], u);
    for(int &v : g[ u ]) {
        if( v == par || v == big[ u ] ) continue;
        head[ v ] = v;
        HLD(v, u);
    }
    en[ u ] = t;
}
void construct(int node = 1, int b = 1, int e = n) {
    if( b == e ) {
        tr[ node ].l = ara[ b ];
        return ;
    }
    int m = (b + e) >> 1, lson = node << 1, rson = lson | 1;
    construct(lson, b, m);
    construct(rson, m + 1, e);
    tr[ node ].l = (tr[ lson ].l + tr[ rson ].l) % mod;
}

void propagate(int node, int b, int e) {
    tr[ node ].s = (tr[ node ].s + (e - b + 1) * 1LL * tr[ node ].v) % mod;
    tr[ node ].s = (tr[ node ].s + tr[ node ].l * tr[ node ].k) % mod;
    if( b != e ) {
        int lson = node << 1;
        int rson = lson | 1;
        tr[ lson ].v = (tr[ lson ].v + tr[ node ].v) % mod;
        tr[ rson ].v = (tr[ rson ].v + tr[ node ].v) % mod;
        tr[ lson ].k = (tr[ lson ].k + tr[ node ].k) % mod;
        tr[ rson ].k = (tr[ rson ].k + tr[ node ].k) % mod;
    }
    tr[ node ].v = tr[ node ].k = 0;
}
void update(int node = 1, int b = 1, int e = n) {
    propagate(node, b, e);
    if( e < l || b > r ) return ;
    if( l <= b && e <= r ) {
        tr[ node ].v = (tr[ node ].v + V) % mod;
        tr[ node ].v = (tr[ node ].v + mod) % mod;
        tr[ node ].k = (tr[ node ].k + K) % mod;
        tr[ node ].k = (tr[ node ].k + mod) % mod;
        propagate(node, b, e);
        return ;
    }
    int m = (b + e) / 2;
    int lson = node + node;
    int rson = lson + 1;
    update(lson, b, m);
    update(rson, m + 1, e);
    tr[ node ].s = (tr[ lson ].s + tr[ rson ].s) % mod;
}
ll query(int node = 1, int b = 1, int e = n) {
    propagate(node, b, e);
    if( e < l || b > r ) return 0LL;
    if( l <= b && e <= r ) return tr[ node ].s;

    int m = (b + e) >> 1;
    int lson = node << 1;
    int rson = lson | 1;
    return (query(lson, b, m) + query(rson, m + 1, e)) % mod;
}
ll queryPath(ll u, ll v) {
    ll ret = 0;
    while( head[ u ] != head[ v ] ) {
        if( d[ head[ u ] ] > d[ head[ v ] ] ) {
            l = st[ head[ u ] ], r = st[ u ];
            ret = (ret + query()) % mod;
            u = p[ head[ u ] ];
        } else {
            l = st[ head[ v ] ], r = st[ v ];
            ret = (ret + query()) % mod;
            v = p[ head[ v ] ];
        }
    }
    if( d[ u ] < d[ v ] ) {
        l = st[ u ], r = st[ v ];
        ret += query();
    }
    else {
        l = st[ v ], r = st[ u ];
        ret += query();
    }
    return ret % mod;

}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q >> r;

    int edge = n - 1;
    while( edge-- ) {
        int u, v;
        cin >> u >> v;
        g[ u ].push_back( v );
        g[ v ].push_back( u );
    }

    dfs( r, 0 );
    HLD( r, 0 );

    for(int i = 1; i <= n; i += 1)
        ara[ st[ i ] ] = d[ i ];
    construct(1, 1, n);

    while( q-- ) {
        char op;
        cin >> op;

        if( op == 'U' ) {
            int x;
            cin >> x >> V >> K;
            l = st[ x ], r = en[ x ];
            update();
            V = (((-d[ x ] * 1LL * K) % mod) + mod) % mod, K = 0;
            update();
        } else {
            int a, b;
            cin >> a >> b;
            ll ans = queryPath(a, b);
            if( ans < 0 ) ans += mod;
            cout << ans << '\n';
        }
    }
    return 0;
}

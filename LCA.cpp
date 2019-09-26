// Codeforces 916E
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll N = 2e5 + 1, LOG = 20;

ll n, q, t, a[ N ], d[ N ], st[ N ], en[ N ];
ll val, l, r, arr[ N ], root, p[ N ][ LOG ];
ll lazy[ N << 1 ], tree[ N << 1 ];
vector<ll> g[ N ];

void dfs(ll u = 1, ll par = 0) {
    d[ u ] = d[ par ] + 1;

    p[ u ][ 0 ] = par;
    for(ll i = 1; i < LOG; i += 1)
        p[ u ][ i ] = p[ p[ u ][ i - 1 ] ][ i - 1 ];

    st[ u ] = ++t;
    arr[ t ] = a[ u ];
    for(ll v : g[ u ]) {
        if( v == par ) continue;
        dfs(v, u);
    }
    en[ u ] = t;
}
ll getSon(ll u) {
    ll v = root;
    ll c = d[ root ] - d[ u ] - 1;
    for(ll i = LOG - 1; ~i; i -= 1) {
        if(c & (1 << i) )
            v = p[ v ][ i ];
    }
    return v;
}
void construct(ll node = 1, ll b = 1, ll e = n) {
    if( b == e ) {
        tree[ node ] = arr[ b ];
        return ;
    }
    ll m = (b + e) >> 1;
    construct(node << 1, b, m);
    construct(node << 1 | 1, m + 1, e);
    tree[ node ] = tree[ node << 1 ] + tree[ node << 1 | 1 ];
}
void propagate(ll node, ll b, ll e) {
    if( lazy[ node ] ) {
        tree[ node ] += (e - b + 1) * 1LL * lazy[ node ];
        if( b != e ) {
            lazy[ node << 1 ] += lazy[ node ];
            lazy[ node << 1 | 1 ] += lazy[ node ];
        }
        lazy[ node ] = 0;
    }
}
void update(ll node = 1, ll b = 1, ll e = n) {
    propagate(node, b, e);
    if( b > e || e < l || b > r ) return ;
    if( l <= b && e <= r ) {
        lazy[ node ] += val;
        propagate(node, b, e);
        return ;
    }
    ll m = (b + e) >> 1;
    update(node << 1, b, m);
    update(node << 1 | 1, m + 1, e);
    tree[ node ] = tree[ node << 1 ] + tree[ node << 1 | 1 ];
}
ll query(ll node = 1, ll b = 1, ll e = n) {
    propagate(node, b, e);
    if( b > e || e < l || b > r ) return 0;
    if( l <= b && e <= r ) return tree[ node ];
    ll m = (b + e) >> 1;
    return query(node << 1, b, m) + query(node << 1 | 1, m + 1, e);
}
ll getLCA(ll u, ll v) {
    if( d[ u ] < d[ v ] ) swap(u, v);
    for(ll i = LOG - 1; ~i; i -= 1)
        if( d[ p[ u ][ i ] ] >= d[ v ])
            u = p[ u ][ i ];
    if( v == u ) return u;
    for(ll i = LOG - 1; ~i; i -= 1)
        if( p[ u ][ i ] != p[ v ][ i ] )
            u = p[ u ][ i ], v = p[ v ][ i ];
    return p[ u ][ 0 ];
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;
    for(ll i = 1; i <= n; i += 1)
        cin >> a[ i ];

    for(ll i = 1; i < n; i += 1) {
        ll u, v;
        cin >> u >> v;
        g[ u ].push_back( v );
        g[ v ].push_back( u );
    }

    dfs();
    construct();
    root = 1;

    while( q-- ) {
        ll op;
        cin >> op;
        if( op == 1 ) {
            cin >> root;
        } else if( op == 2 ) {
            ll u, v, x;
            cin >> u >> v >> x;


            ll A = getLCA(u, root);
            ll B = getLCA(v, root);
            ll C = getLCA(u, v);

            if( d[ C ] < d[ A ]) swap(C, A);
            if( d[ C ] < d[ B ]) swap(C, B);

            if( st[ C ] <= st[ root ] && st[ root ] <= en[ C ] ) {
                l = 1, r = n, val = x, update();
                if( C == root ) continue;
                ll son = getSon(C);
                l = st[ son ], r = en[ son ], val = -x, update();
            } else {
                l = st[ C ], r = en[ C ], val = x;
                update();
            }
        } else {
            ll v;
            cin >> v;

            ll ans = 0;

            if( v == root ) {
                l = 1, r = n, ans = query();
            } else if( st[ v ] <= st[ root ] && st[ root ] <= en[ v ] ) {
                l = 1, r = n, ans = query();
                ll son = getSon(v);
                l = st[ son ], r = en[ son ], ans -= query();
            } else {
                l = st[ v ], r = en[ v ], ans = query();
            }
            cout << ans << '\n';
        }
    }
    return 0;
}

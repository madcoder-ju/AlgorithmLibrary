/*
 * CodeMarshal RUET IUPC 2019 D
 * idea: 
 * let A be an array. The polynomial hash of a segment [l, r] can be defined as
 * H[l, r] = (frequency of A[ i ] in the range [l, r]) * (X ^ A[ i ]), X is a prime
 * A = {1, 2, 2, 4, 2, 3, 3, 5};
 * H[2, 5] = 3 * X ^ 2 + X ^ 4 + 2 * X ^ 3
 */
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll N = 2e5 + 1;
const ll MOD = 179424691;

ll n, t, l, r, val, a[ N ], st[ N ], en[ N ], ara[ N ];
ll x[ N ], xinv[ N ], tree[ N << 2 ], lazy[ N << 2 ];
vector<ll> g[ N ];

ll power(ll b, ll p) {
    ll ret = 1LL;
    while( p ) {
        if( p & 1 ) ret = (ret * b) % MOD;
        b = (b * b) % MOD;
        p >>= 1LL;
    }
    return ret;
}

void dfs(ll u = 1, ll par = 0) {
    st[ u ] = ++t;
    ara[ t ] = a[ u ];
    for(ll v : g[ u ]) {
        if( v == par ) continue;
        dfs(v, u);
    }
    en[ u ] = t;
}

void construct(ll node = 1, ll b = 1, ll e = n) {
    lazy[ node ] = 0;
    if( b == e ) {
        if( ara[ b ] < 0 ) tree[ node ] = xinv[ -ara[ b ] ];
        else tree[ node ] = x[ ara[ b ] ];
        return;
    }
    ll m = (b + e) >> 1;
    construct(node << 1, b, m);
    construct(node << 1 | 1, m + 1, e);
    tree[ node ] = (tree[ node << 1 ] + tree[ node << 1 | 1 ]) % MOD;
}

void propagate(ll node, ll b, ll e) {
    if( lazy[ node ] ) {
        ll add;
        if( lazy[ node ] < 0 ) add = power(power(67, -lazy[ node]), MOD - 2);
        else add = power(67, lazy[ node ]);
        tree[ node ] = (tree[ node ] * 1LL * add) % MOD;
        if( b != e ) {
            lazy[ node << 1 ] += lazy[ node ];
            lazy[ node << 1 | 1 ] += lazy[ node ];
        }
        lazy[ node ] = 0;
    }
}
void update(ll node = 1, ll b = 1, ll e = n) {
    propagate(node, b, e);
    if( b > e || b > r || e < l ) return ;
    if( l <= b && e <= r ) {
        lazy[ node ] += val;
        propagate(node, b, e);
        return ;
    }
    ll m = (b + e) >> 1;
    update(node << 1, b, m);
    update(node << 1 | 1, m + 1, e);
    tree[ node ] = (tree[ node << 1 ] + tree[ node << 1 | 1 ]) % MOD;
}

ll query(ll node = 1, ll b = 1, ll e = n) {
    propagate(node, b, e);
    if( b > e || b > r || e < l ) return 0LL;
    if( l <= b && e <= r ) return tree[ node ];
    ll m = (b + e) >> 1;
    return (query(node << 1, b, m) + query(node << 1 | 1, m + 1, e)) % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    x[ 0 ] = 1;
    xinv[ 0 ] = power(x[ 0 ], MOD - 2);
    for(ll i = 1; i < N; i += 1) {
        x[ i ] = (x[ i - 1 ] * 67) % MOD;
        xinv[ i ] = power(x[ i ], MOD - 2);
    }



    ll testcase, caseno = 1;
    cin >> testcase;
    while( testcase-- ) {
        ll q;
        cin >> n >> q;

        for(ll i = 1; i <= n; i += 1) {
            cin >> a[ i ];
        }

        for(ll i = 1; i <= n; i += 1)
            g[ i ].clear();

        ll edge = n - 1;
        while( edge-- ) {
            ll u, v;
            cin >> u >> v;
            g[ u ].push_back( v );
            g[ v ].push_back( u );
        }

        t = 0;
        dfs();
        construct();

        cout << "Case " << caseno++ << ":\n";
        while( q-- ) {
            ll op;
            cin >> op;
            if( op == 1 ) {
                ll v;
                cin >> v >> val;
                l = st[ v ];
                r = en[ v ];
                update();
            } else {
                ll u, v;
                cin >> u >> v;
                l = st[ u ];
                r = en[ u ];
                ll ans = query();
                l = st[ v ];
                r = en[ v ];
                ans -= query();
                if( ans == 0 ) cout << 1 << '\n';
                else cout << 0 << '\n';
            }
        }
    }

    return 0;
}

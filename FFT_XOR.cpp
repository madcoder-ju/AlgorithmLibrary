/*
 * CS Academy 
 * generate an array of size N where each element is a random integer 
 * between 0 and K (inclusive). count the number of possible arrays 
 * where the xor sum of the elments is strictly greater than 0
 */
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll mod = 30011;

ll bigmod(ll b, ll p) {
    ll ret = 1LL;
    while( p ) {
        if( p & 1 )
            ret = (ret * b) % mod;
        b = (b * b) % mod;
        p >>= 1;
    }
    return ret;
}

void xorfft(vector<ll> &P, bool inv) {
    int n = (int)P.size();
    for(int l = 1; (l << 1) <= n; l <<= 1) {
        for(int i = 0; i < n; i += (l << 1)) {
            for(int j = 0; j < l; j += 1) {
                ll u = P[ i + j ], v = P[ i + l + j ];
                P[ i + j ] = (u + v) % mod;
                P[ i + l + j ] = ( u - v ) % mod;
            }
        }
    }
    if(inv) {
        ll x = bigmod(n * 1LL, mod - 2);
        for(int i = 0; i < n; i += 1)
            P[ i ] = (P[ i ] * x) % mod;
    }
}
int main() {
    int n, k; cin >> n >> k;

    int N = 1;
    while(N < k) N <<= 1;
    N <<= 1;

    vector<ll> coefficient(k + 1, 1);
    coefficient.resize(N);

    xorfft(coefficient, 0);
    for(ll &x : coefficient)
        x = bigmod(x, n);
    xorfft(coefficient, 1);

    for(int i = 0; i < N; i += 1)
        if(coefficient[i] < 0) coefficient[i] += mod;

    ll res = 0;
    for(int i = 1; i < N; i += 1)
        res = (res + coefficient[ i ]) % mod;
    cout << res << '\n';
    return 0;
}

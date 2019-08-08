#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll MOD, ROOT;

ll bigmod(ll b, ll p) {
    ll ret = 1LL;
    while( p ) {
        if( p & 1 )
            ret = (ret * b) % MOD;
        b = (b * b) % MOD;
        p >>= 1;
    }
    return ret;
}

ll generateRoot(ll p) {
    vector<ll>fact;
    ll phi = p - 1, n = p - 1;
    for(int i = 2; i * i <= n; i += 1) {
        if(n % i == 0) {
            fact.push_back(i);
            while( n % i == 0 )
                n /= i;
        }
    }
    if(n > 1)
        fact.push_back(n);
    for(ll res = 2; res <= p; res += 1) {
        bool ok = 1;
        for(size_t i = 0; i < fact.size() && ok; i += 1)
            ok &= bigmod( res, phi / fact[ i ]) != 1;
        if( ok )
            return res;
    }
    return -1;
}

// cs academy: and closure
// link: https://csacademy.com/contest/archive/task/and-closure/
void andfft(vector<ll> &P, bool inv) {
    int n = (int)P.size();
    for(int l = 1; (l << 1) <= n; l <<= 1) {
        for(int i = 0; i < n; i += (l << 1)) {
            for(int j = 0; j < l; j += 1) {
                ll u = P[ i + j ], v = P[ i + l + j ];
                if( !inv )
                    P[ i + j ] = v, P[ i + l + j ] = (u + v) % MOD;
                else
                    P[ i + j ] = (-u + v) % MOD, P[ i + l + j ] = u;
            }
        }
    }
}

// not found yet
void orfft(vector<ll> &P, bool inv) {
    int n = (int)P.size();
    for(int l = 1; (l << 1) <= n; l <<= 1) {
        for(int i = 0; i < n; i += (l << 1)) {
            for(int j = 0; j < l; j += 1) {
                ll u = P[ i + j ], v = P[ i + l + j ];
                if( !inv )
                    P[ i + j ] = (u + v) % MOD, P[ i + l + j ] = u;
                else
                    P[ i + j ] = v, P[ i + l + j ] = (u - v) % MOD;
            }
        }
    }
}

// cs academy: random nim generator
// link: https://csacademy.com/contest/archive/task/random_nim_generator/
void xorfft(vector<ll> &P, bool inv) {
    int n = (int)P.size();
    for(int l = 1; (l << 1) <= n; l <<= 1) {
        for(int i = 0; i < n; i += (l << 1)) {
            for(int j = 0; j < l; j += 1) {
                ll u = P[ i + j ], v = P[ i + l + j ];
                P[ i + j ] = (u + v) % MOD;
                P[ i + l + j ] = ( u - v ) % MOD;
            }
        }
    }
    if(inv) {
        ll x = bigmod(n * 1LL, MOD - 2);
        for(int i = 0; i < n; i += 1)
            P[ i ] = (P[ i ] * x) % MOD;
    }
}


// codeforces: 1096G - lucky tickets
// link: http://codeforces.com/problemset/problem/1096/G
void NTT(vector<ll> &a, bool inv) {
    int n = (int)a.size();
    for(int i = 1, j = 0; i < n; i += 1) {
        int bit = n >> 1;
        for(; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if( i < j )
            swap(a[ i ], a[ j ]);
    }
    for(int l = 2; l <= n; l <<= 1) {
        ll wlen = bigmod(ROOT, (MOD - 1) / l);
        if( inv )
            wlen = bigmod(wlen, MOD - 2);
        for(int i = 0; i < n; i += l) {
            ll w = 1LL;
            for(int j = 0; j < l / 2; j += 1) {
                ll u = a[ i + j ], v = a[ i + j + l / 2 ] * w;
                v %= MOD;
                a[ i + j ] = (u + v) % MOD;
                a[ i + j + l / 2 ] = (u - v) % MOD;
                w *= wlen;
                w %= MOD;
            }
        }
    }
    if(inv) {
        ll x = bigmod(n * 1LL, MOD - 2);
        for(int i = 0; i < n; i += 1) {
            a[ i ] = (a[ i ] * x) % MOD;
        }
    }
}

/*
 * fft(vector<ll> &coe, int len): co is the coefficient vector, len is the length
 * of the sequence we want to build. after this function we get a vector which
 * represents the number of ways we can make a sequence of length "len" having bitwise
 * and/or/xor or digit sum( for NTT ).
 * in short, before, coe[ i ] = the coefficient of (x ^ i), i is input value
 *           after, coe[ i ] = number of ways i (and/or/xor/digit sum) can be find 
 *                  where length of the sequence is len.
 * basically it evaluates the all possible subset sums where the set is of "len" length
 * initially 
 */
void fft(vector<ll> &coe, int len) {
    // MOD = 5767169; andfft(coe, 0); // MOD was not given
    // MOD = 5767169; orfft(coe, 0); // MOD was not given
     MOD = 30011; xorfft(coe, 0); // MOD was given
    // MOD = ; ROOT = generate(MOD); NTT(coe, 0);
    for(auto &x : coe) 
        x = bigmod(x, len);
    // andfft(coe, 1);
    // orfft(coe, 1);
     xorfft(coe, 1);
    // NTT(coe, 1);
    for(auto &x: coe) 
        if( x < MOD ) x += MOD;
}
int main() {
    int n, k;
    cin >> n >> k;

    // initialize the size of the "coe" with the closest power of 2 of the max sum
    vector<ll> coe(k + 1, 1);
    int Max2 = 1;
    while( Max2 < k )
        Max2 <<= 1;
    Max2 <<= 1;
    coe.resize(Max2);

    fft(coe, n);

    ll ans = 0;
    for(int i = 1; i < Max2; i += 1) {
        if( coe[ i ] ) ans += coe[ i ];
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}

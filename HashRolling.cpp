/*
 * find the position of P as a substring of S
 */
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const int N = 3e5 + 35;

const ll base1 = 191, base2 = 307;
const ll mod1 = 1000001011, mod2 = 1000009999;

ll pow1[ N ], pow2[ N ];

struct PolyHash {

    vector<pair<ll, ll>> h;
   
    // Polyhash(string &s): a constructor, makes the hash of string S
    PolyHash(string &s) {
        ll x = 0, y = 0;
        for(char ch : s) {
            x = (x * base1 + ch) % mod1;
            y = (y * base2 + ch) % mod2;
            h.push_back({x, y});
        }
    }
    
    void reset(string &s) {
        h.clear();
        ll x = 0, y = 0;
        for(char ch : s) {
            x = (x * base1 + ch) % mod1;
            y = (y * base2 + ch) % mod2;
            h.push_back({x, y});
        }
    }
    
    // getHash(int l, int r): gives the hash value of the substring S[l, r]
    pair<ll, ll> getHash(int l, int r) {
        ll x = h[ r ].first;
        ll y = h[ r ].second;
        if( l == 0 ) return {x, y};
        x = (x - (h[ l - 1 ].first * pow1[ r - l + 1 ]) % mod1 + mod1) % mod1;
        y = (y - (h[ l - 1 ].second * pow2[ r - l + 1 ]) % mod2 + mod2) % mod2;
        return {x, y};
    }
};

int main() {

    // precalculation of bases powers
    pow1[ 0 ] = pow2[ 0 ] = 1;
    for(int i = 1; i < N; i += 1) {
        pow1[ i ] = (pow1[ i - 1 ] * base1) % mod1;
        pow2[ i ] = (pow2[ i - 1 ] * base2) % mod2;
    }

    string s, p;
    cin >> s >> p;

    PolyHash a(s), b(p);
    int len = (int)p.size();



    pair<ll,ll> need = b.getHash(0, len - 1);
    for(int i = 0; i + len - 1 < s.size( ); i += 1) {
        auto x = a.getHash(i, i + len - 1);
        if( need == x ) {
            cout << i << ' ';
        }
    }
    cout << '\n';
    return 0;
}

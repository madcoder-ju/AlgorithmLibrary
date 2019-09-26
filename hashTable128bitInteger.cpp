// CodeMarshal DUET IUPC 2019 I
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#pragma GCC opimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC opimize("unroll-loops")

const int N = 262150, LOG = 19;
typedef unsigned __int128 ull;

ull pw[ N ], a[ N ];

struct Hash {
    int operator()(ull x) const {
        return (x ^ (x >> 32) ^ (x >> 64));
    }
};

gp_hash_table<ull, int, Hash> cnt[ LOG ];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ull base = 67;
    pw[ 0 ] = 1;
    for(int i = 1; i < N; i += 1)
        pw[ i ] = pw[ i - 1 ] * base;
    int testcase, caseno = 1;
    cin >> testcase;

    while( testcase-- ) {
        string s;
        cin >> s;


        for(int i = 0; s[ i ]; i += 1) {
            if( i == 0 )
                a[ i ] = s[ i ];
            else
                a[ i ] = a[ i - 1 ] * base + s[ i ];
        }

        for(int i = 0; i < LOG; i += 1) {
            for(int k = 0; k + (1 << i) - 1 < (int)s.size(); k += 1 ) {
                ull h = a[ k + (1 << i) - 1] - (k ? a[ k - 1 ] * pw[ 1 << i ] : 0);
                cnt[ i ][ h ] += 1;
            }
        }

        int q;
        cin >> q;

        cout << "Case " << caseno++ << ":\n";
        while( q-- ) {
            string p;
            cin >> p;

            ull h = 0;
            for(int i = 0; p[ i ]; i += 1) {
                h = h * base + p[ i ];
            }

            int l = 31 - __builtin_clz((int)p.size());


            long long ans = 0;
            if( cnt[ l ].find(h) != cnt[ l ].end() ) {
                ans += cnt[ l ][ h ];
            }

            for(int i = 0; p[ i ]; i += 1) {
                for(int k = 0; k < 16; k += 1) {
                    char ch = 'a' + k;
                    if( ch == p[ i ] )
                        continue;
                    ull x = h + (ch - p[ i ]) * pw[ (1 << l) - i - 1 ];
                    if( cnt[ l ].find(x) != cnt[ l ].end() )
                        ans += cnt[ l ][ x ];
                }
            }
            cout << ans << '\n';
        }

        for(int i = 0; i < LOG; i += 1) {
            cnt[ i ].clear();
        }
    }
    return 0;
}

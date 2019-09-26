/* 
 * CS Academy: And Closure
 * given an array of N integers. choose any subset of numbers and compute
 * their binary and. find the number of distinct results you can get.
 */
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll MOD = 5767169;

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
void andfft(vector<ll> &P, bool inv) {
    int n = (int)P.size();
    for(int l = 1; (l << 1) <= n; l <<= 1) {
        for(int i = 0; i < n; i += (l << 1)) {
            for(int j = 0; j < l; j += 1) {
                ll u = P[ i + j ], v = P[ i + l + j ];
                if( !inv )
                    P[ i + j ] = v, P[ i + l + j ] = (u + v) % MOD;
                    // P[ i + j ] = (u + v) % MOD, P[ i + l + j ] = u; // for orfft
                else
                    P[ i + j ] = (-u + v) % MOD, P[ i + l + j ] = u;
                    // P[ i + j ] = v, P[ i + l + j ] = (u - v) % MOD; // for orfft
            }
        }
    }
}
int main() {
    int n; cin >> n;
    vector<ll> A(1 << 20, 0);
    for(int i = 1; i <= n; i += 1) {
        int x; cin >> x; A[ x ] = 1;
    }
    
    andfft(A, 0);
    for(auto &x : A) 
        x = ( bigmod(x, n) + MOD ) % MOD;
    andfft(A, 1);
    
    int ans = 1;
    for(int i = 1; i < (1 << 20); i += 1)
        if( A[ i ] ) ans += 1;
    cout << ans << '\n';
    return 0;
}

/*
 * Codeforces 1096G
 * given n(even). find the number of different lucky tickets modulo 998244353. 
 * a ticket is lucky if the sum of first n/2 digits is equal to the sum of 
 * remaining n/2 digits.
 */
#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
const ll mod = 998244353, root = 3;
 
ll bigmod(ll b, ll p) {
	ll ret = 1LL;
	while( p ) {
		if( p & 1 ) ret = (ret * b) % mod;
		b = (b * b) % mod;
		p >>= 1;
	}
	return ret;
}
 
 
void NTT(vector<ll> &a, bool inv) {
	int n = (int)a.size();
	for(int i = 1, j = 0; i < n; i += 1) {
		int bit = n >> 1;
		for(; j >= bit; bit >>= 1)
			j -= bit;
        j += bit;
		if( i < j ) swap(a[ i ], a[ j ]);
	}
	for(int l = 2; l <= n; l <<= 1) {
		ll wlen = bigmod(root, (mod - 1) / l);
		if( inv )
			wlen = bigmod(wlen, mod - 2);
		for(int i = 0; i < n; i += l) {
			ll w = 1LL;
			for(int j = 0; j < l / 2; j += 1) {
				ll u = a[ i + j ], v = a[ i + j + l / 2 ] * w;
				v %= mod;
				a[ i + j ] = (u + v) % mod;
				a[ i + j + l / 2 ] = (u - v) % mod;
				w *= wlen;
				w %= mod;
			}
		}
	}
	if(inv) {
		ll x = bigmod(n * 1LL, mod - 2);
		for(int i = 0; i < n; i += 1) {
			a[ i ] = (a[ i ] * x) % mod;
		}
	}
}
int main() {
	int n, k;
	cin >> n >> k;
 
	vector<ll> A(1 << 20, 0);
	for(int i = 1; i <= k; i += 1) {
		int x;
		cin >> x;
		A[ x ] = 1;
	}
 
	NTT(A, 0);
	for(ll &x : A)
		x = bigmod(x, n / 2LL);
	NTT(A, 1);
 
	ll ans = 0;
	for(auto x : A) {
		ans = (ans + (x * x) % mod ) % mod;
	}
	cout << ans << '\n';
	return 0;
}

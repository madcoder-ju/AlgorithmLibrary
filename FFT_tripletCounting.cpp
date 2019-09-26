/*
 *  Topcoder: Counting Triplets
 * given an array A of n integers. find the number of fibonacci 
 * triplets.
 * a triplet i < j < k called fibonacci triplet if A[ i ] + A[ j ] = A[ k ]
 */
#include <bits/stdc++.h>

using namespace std;

using D = double;
using ll = long long;
const int N = 1 << 17;
const D PI = acos(-1);

int a[ N ], nxt[ 1 << 16 + 1 ], pre[ 1 << 16 + 1 ], tmp[ 1 << 16 + 1 ];

struct Complex {
    D r,i;
    Complex() : r(0), i(0) {}
    Complex(D r) : r(r), i(0) {}
    Complex(D r, D i): r(r), i(i) {}
    D real() { return r; }
    Complex operator + (Complex w) { return Complex( r + w.r, i + w.i); }
    Complex operator - (Complex w) { return Complex( r - w.r, i - w.i); }
    Complex operator /= (D x) { r /= x, i /= x; return *this; }
    Complex operator *(Complex w){return Complex(r * w.r - i * w.i,r * w.i + i * w.r);}
    Complex operator *=(Complex w){return *this=Complex(r*w.r - i*w.i, r*w.i + i*w.r);}
};
void fft(vector<Complex> &a, bool inv) {
    int n = (int)a.size();
    for(int i = 1, j = 0; i < n; i += 1) {
        int bit = n >> 1;
        for( ; j >= bit; bit >>= 1)
            j -= bit;
        j += bit ;
        if( i < j ) swap(a[i],a[j]);
    }
    for(int len = 2; len <= n; len <<= 1) {
        D ang = 2.0 * PI / len * ( inv ? -1 : 1 );
        Complex wlen( cos(ang), sin(ang) );
        for(int i = 0; i < n; i += len) {
            Complex w(1) ;
            for(int j = 0; j < len / 2; j += 1) {
                Complex u = a[ i + j ], v = a[ i + j + len / 2 ] * w;
                a[ i + j ] = u + v ;
                a[ i + j + len / 2 ] = u - v;
                w *= wlen ;
            } } }
    if(inv)
        for(int i = 0; i < n; i += 1) a[ i ] /= n ;
}

vector<ll> multiply(vector<ll> &a, vector<ll> &b) {
	int k = a.size() + b.size(), n = 1;
	while( n < k) n <<= 1;
	vector<Complex>fa(a.begin(),a.end()), fb(b.begin(),b.end());
  	fa.resize(n); fb.resize(n);
  	fft(fa,0); fft(fb, 0);
  	for(int i = 0; i < n; i += 1) fa[ i ] *= fb[ i ];
  	fft(fa, 1); 
  	vector<ll>ret( n );
  	for(int i = 0; i < n; i += 1)
    	ret[ i ] = round(fa[ i ].r);
  	
  	return ret;
}

int main() {
	int testcase, caseno = 1;
	scanf("%d", &testcase);

	while( testcase-- ) {
		memset(nxt, 0, sizeof nxt);
		memset(pre, 0, sizeof pre);
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i += 1) {
			scanf("%d", &a[ i ]);
			nxt[ a[ i ] ] += 1;
		}

		ll ans = 0;
		int st = 0, en = 0, block = 3510;
		while( en < n ) {
			st = en + 1;
			en = min(n, st + block);

			for(int i = st; i <= en; i += 1) {
				nxt[ a[ i ] ] -= 1;
			}

			for(int i = en; i >= st; i -= 1) {
				for(int j = i - 1; j >= st; j -= 1) {
					ans += nxt[ a[ i ] + a[ j ] ];
					ans += tmp[ a[ i ] + a[ j ] ];
					if( a[ i ] > a[ j ] ) ans += pre[ a[ i ] - a[ j ] ];
				}
				tmp[ a[ i ] ] += 1; 
			}

			vector<ll> A(1 << 16), B(1 << 16);
			for(int i = 1; i < (1 << 16); i += 1) {
				A[ i ] = pre[ i ];
				B[ i ] = nxt[ i ];
			}
			reverse(B.begin(), B.end());
			vector<ll> C = multiply(A, B);
			for(int i = st; i <= en; i += 1) {
				ans += C[ ((1 << 16) - 1) - a[ i ] ];
				tmp[ a[ i ] ] -= 1;
				pre[ a[ i ] ] += 1;
			}
		} 
		printf("%lld\n", ans);
	}
	return 0;
}

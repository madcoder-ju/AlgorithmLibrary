/*
 * SPOJ ADAMATCH: Ada and Nucleobase
 * find the minimum mismatch between P and substrings of T. 
 */
#include <bits/stdc++.h>

using namespace std;

using D = double;
using ll = long long;
const int N = 1 << 20;

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
        D ang = 2.0 * acos(-1.0) / len * ( inv ? -1 : 1 );
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

string p, t;
ll ans[ N ];

void foo(char ch) {
	vector<ll> a, b, c;
	for(char x : p) 
		(x == ch ) ? a.push_back(1) : a.push_back(0);
	for(char x : t) 
		(x == ch) ? b.push_back(1) : b.push_back(0);
	reverse(b.begin(), b.end());
	c = multiply(a, b);
	for(int i = 0; i < c.size(); i += 1) {
		ans[ i ] += c[ i ];
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> t >> p;
	foo('A'); foo('C'); foo('T'); foo('G');
	ll mx = 0;
	for(int i = p.size() - 1; i < t.size(); i += 1) 
		mx = max(mx, ans[ i ]);
	cout << p.size() - mx << '\n';
	return 0;
}

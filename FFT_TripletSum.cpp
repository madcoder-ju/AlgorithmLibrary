/*
 * SPOJ TSUM
 * given an array A of n distinct integers where A[ i ] <= 20000
 * for each obtainable sum output the number of different triples of 
 * indicies that generate it.
 * a triplets is a sequence where positions i < j < k   
 */
#include <bits/stdc++.h>

using namespace std;

using D = double;
using ll = long long;

const D PI = acos(-1);
const int N = 1 << 17;

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
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin >> n;
    vector<Complex> A(N), B(N), C(N), ans(N);
    for(int i = 1; i <= n; i += 1) {
        int x; cin >> x; x += 20000;
        A[ x ].r = B[ x + x ].r = C[ x + x + x ].r = 1;
    }

    fft(A, 0); fft(B, 0);
    for(int i = 0; i < N; i += 1)
        ans[ i ] = A[ i ] * ( A[ i ] * A[ i ] - B[ i ] - B[ i ] - B[ i ] );
    fft(ans, 1);

    for(int i = 0; i < N; i += 1) {
        ll res = ((ll)(ans[ i ].r + 0.5) + 2 * C[ i ].r) / 6;
        if( res > 0 ) cout << i - 60000 << " : " << res << '\n';
    }
    return 0;
}
\end{minted}
\newpage
\section*{2. CS Academy: Random Nim Generator (40 ms)}
\subsection*{tags: all possible subset xor }
\begin{minted}[frame=lines, linenos, fontsize=\large]
{c++}
/*
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

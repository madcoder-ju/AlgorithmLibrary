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


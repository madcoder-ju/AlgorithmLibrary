#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const int N = 1e5 + 1;

int n, l, r, pos, x, a[ N ], t[ N << 2 ];

void construct(int node = 1, int b = 1, int e = n) {
    if( b == e ) {
        t[ node ] = a[ b ];
        return ;
    }
    int m = (b + e) >> 1;
    construct(node << 1, b, m);
    construct(node << 1 | 1, m + 1, e);
    t[ node ] = t[ node << 1 ] + t[ node << 1 | 1 ];
}

void update(int node = 1, int b = 1, int e = n) {
    if( b == e ) {
        t[ node ] = x;
        return;
    }
    int m = (b + e) >> 1;
    if( pos <= m ) update(node << 1, b, m);
    else update(node << 1 | 1, m + 1, e);
    t[ node ] = t[ node << 1 ] + t[ node << 1 | 1 ];
}
ll query(int node = 1, int b = 1, int e = n) {
    if( b > e || b > r || e < l ) return 0;
    if( l <= b && e <= r ) {
        return t[ node ];
    }
    int m = (b + e) >> 1;
    int P = query(node << 1, b, m);
    int Q = query(node << 1 | 1, m + 1, e);
    return P + Q;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i += 1)
        cin >> a[ i ];

    construct();

    int q;
    cin >> q;
    while( q-- ) {
        int op;
        cin >> op;
        if( op == 1 ) {
            cin >> l >> r;
            cout << query() << '\n';
        } else {
            cin >> l >> r >> x;
            update();
        }
    }
    return 0;
}

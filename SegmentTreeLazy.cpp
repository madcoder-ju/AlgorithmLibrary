#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int M = 1e5 + 15;
int n, l, r;
ll val;
ll tree[ M << 2 ];
ll lazy[ M << 2 ];

void construct(int node = 1, int b = 1, int e = n) {
    lazy[ node ] = 0;
    if( b == e ) {
        tree[ node ] = 0;
        return ;
    }

    int m = (b + e) >> 1;
    construct(node << 1, b, m);
    construct(node << 1 | 1, m + 1, e);

    tree[ node ] = tree[ node << 1 ] + tree[ node << 1 | 1 ];
}

void propagate(int node, int b, int e) {
    if( lazy[ node ] != 0 ) {
        tree[ node ] += (e - b + 1) * 1LL * lazy[ node ];
        if( b != e ) {
            lazy[ node << 1 ] += lazy[ node ];
            lazy[ node << 1 | 1 ] += lazy[ node ];
        }
        lazy[ node ] = 0;
    }
}
void update(int node = 1, int b = 1, int e = n) {
    propagate(node, b, e);
    if( b > e || b > r || e < l ) return ;
    if( l <= b && e <= r ) {
        lazy[ node ] += val;
        propagate(node, b, e);
        return ;
    }
    int m = (b + e) >> 1;
    update(node << 1, b, m);
    update(node << 1 | 1, m + 1, e);

    tree[ node ] = tree[ node << 1 ] + tree[ node << 1 | 1 ];
}
ll query(int node = 1, int b = 1, int e = n) {
    propagate(node, b, e);
    if( b > e || b > r || e < l ) return 0LL;
    if( l <= b && e <= r ) {
        return tree[ node ];
    }
    int m = (b + e) >> 1;
    ll p = query(node << 1, b, m);
    ll q = query(node << 1 | 1, m + 1, e);
    return p + q;
}
int main() {

    return 0;
}

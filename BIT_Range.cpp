/*
 * LightOJ 1164: Horrible Queries
 * given an array of length n initially all zero and q queries.
 * 0 x y v: add v to all elements in the interval [x, y]
 * 1 x y: print sum of all elements in the interval [x, y]
 * array is 0 indexed
 */
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const int N = 2e5 + 25;

int n;
ll bit1[ N ], bit2[ N ];

void reset() {
    memset(bit1, 0, sizeof bit1);
    memset(bit2, 0, sizeof bit2);
}
void update(ll bit[], int i, ll val) {
    while( i <= n ) {
        bit[ i ] += val;
        i += (i & (-i));
    }
}
void update(int l, int r, ll val) {
    update(bit1, l, val);
    update(bit1, r + 1, -val);
    update(bit2, l, val * (l - 1));
    update(bit2, r + 1, -val * r);
}

ll query(ll bit[], int i) {
    ll ret = 0;
    while( i > 0 ) {
        ret += bit[ i ];
        i -=  (i & (-i));
    }
    return ret;
}
ll query(int l, int r) {
    l -= 1;
    ll p = query(bit1, l) * l - query(bit2, l);
    ll q = query(bit1, r) * r - query(bit2, r);
    return q - p;
}

int main() {
    int testcase, caseno = 1;
    scanf("%d", &testcase);
    while( testcase-- ) {
        int q;
        cin >> n >> q;
        reset();
        printf("Case %d:\n", caseno++);
        while( q-- ) {
            int op, x, y;
            scanf("%d %d %d", &op, &x, &y);
            if( op == 0 ) {
                ll v;
                scanf("%lld", &v);
                update(x + 1, y + 1, v);
            } else {
                printf("%lld\n", query(x + 1, y + 1));
            }
        }
    }
    return 0;
}

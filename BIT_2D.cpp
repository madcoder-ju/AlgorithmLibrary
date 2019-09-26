/*
 * LightOJ 1266: Points in Rectangle
 * given q operations on a 2D coordinate system.
 * 1 x1 y1 x2 y2: print the number of point in the rectangle
 * 0 x1 y1: add a point(x1, y1) if not exists
 * 0 <= x, y <= 1000
 */
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const int N = 1e3 + 13;

ll n, a[ N ][ N ], bit[ N ][ N ];

void update(ll x, ll y, ll val) {
    for(int i = x; i <= n; i += (i & (-i)))
        for(int j = y; j <= n; j += (j & (-j)))
            bit[ i ][ j ] += val;
}
ll query(ll x, ll y) {
    ll ret = 0;
    for(int i = x; i > 0; i -= (i & (-i)))
        for(int j = y; j > 0; j -= (j & (-j)))
            ret += bit[ i ][ j ];
    return ret;
}
int main() {
    int testcase, caseno = 1;
    scanf("%d", &testcase);
    while( testcase-- ) {
        n = 1002; // max x or y value
        memset(a, 0, sizeof a);
        memset(bit, 0, sizeof bit);

        printf("Case %d:\n", caseno++);
        int q;
        scanf("%d", &q);
        while( q-- ) {
            int op;
            scanf("%d", &op);
            if( op ) {
                int x1, y1, x2, y2;
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                x1 += 1; x2 += 1; y1 += 1; y2 += 1;
                int ans = query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
                printf("%d\n", ans);
            } else {
                int x1, y1;
                scanf("%d%d", &x1, &y1);
                x1 += 1; y1 += 1;
                if( !a[ x1 ][ y1 ] ) {
                    a[ x1 ][ y1 ] = 1;
                    update(x1, y1, 1);
                }
            }
        }
    }
    return 0;
}

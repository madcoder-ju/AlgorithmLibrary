/*
 * LightOJ 1207: Posters for Election
 * given n line poster as line segments reresented as l r serially
 * find the number of different posters that are visible
 * 1 <= l, r <= 2n
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 15;

int n, l, r, color, vis[ N << 1 ], tree[ N << 2 ], lazy[ N << 2 ];

void propagate(int node, int b, int e) {
    if( lazy[ node ] ) {
        tree[ node ] = lazy[ node ];
        if( b != e ) {
            lazy[ node << 1 ] = lazy[ node ];
            lazy[ node << 1 | 1 ] = lazy[ node ];
        }
        lazy[ node ] = 0;
    }
}
void update(int node = 1, int b = 1, int e = n + n) {
    propagate(node, b, e);
    if( b > e || b > r || e < l )
        return ;
    if( l <= b && e <= r ) {
        lazy[ node ] = color;
        propagate(node, b, e);
        return ;
    }
    int m = (b + e) >> 1;
    update(node << 1, b, m);
    update(node << 1 | 1, m + 1, e);
    tree[ node ] = tree[ node << 1 ] + tree[ node << 1 | 1 ];
}
int query(int node = 1, int b = 1, int e = n + n) {
    propagate(node, b, e);
    if( b > e || b > r || e < l )
        return 0;
    if( l <= b && e <= r )
        return tree[ node ];
    int m = (b + e) >> 1;
    return query(node << 1, b, m) + query(node << 1 | 1, m + 1, e);
}
int main() {
    int testcase, caseno = 1;
    scanf("%d", &testcase);
    while( testcase-- ) {
        scanf("%d", &n);
        color = 0;
        memset(lazy, 0, sizeof lazy);
        memset(tree, 0, sizeof tree);
        memset(vis, 0, sizeof vis);
        for(int i = 1; i <= n; i += 1) {
            scanf("%d %d", &l, &r);
            color += 1;
            update();
        }
        int ans = 0;
        for(int i = 1; i <= n + n; i += 1) {
            l = r = i;
            int c = query();
            if( c && !vis[ c ] )
                ans += 1, vis[ c ] = 1;
        }
        printf("Case %d: %d\n", caseno++, ans);
    }
    return 0;
}

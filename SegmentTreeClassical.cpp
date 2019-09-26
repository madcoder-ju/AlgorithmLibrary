/*
 * LightOJ 1112: Curious Robin Hood
 * given an array A of n elements and q queries.
 * 1 pos: print A[ pos ] && make A[ pos ] = 0
 * 2 pos v: add v to A[ pos ]
 * 3 l r: print sum of element in the interval [l, r]
 * A is 0 indexed
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 15;

int n, l, r, pos, val, ara[ N ], tree[ N << 2 ];

void construct(int node = 1, int b = 1, int e = n) {
    if( b == e ) {
        tree[ node ] = ara[ b ];
        return ;
    }
    int m = (b + e) >> 1;
    construct(node << 1, b, m);
    construct(node << 1 | 1, m + 1, e);
    tree[ node ] = tree[ node << 1 ] + tree[ node << 1 | 1 ];
}
void update(int node = 1, int b = 1, int e = n) {
    if( b == e ) {
        tree[ node ] += val;
        return ;
    }
    int m = (b + e) >> 1;
    if( pos <= m )
        update(node << 1, b, m);
    else
        update(node << 1 | 1, m + 1, e);
    tree[ node ] = tree[ node << 1 ] + tree[ node << 1 | 1 ];
}
int query(int node = 1, int b = 1, int e = n) {
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
        int q;
        scanf("%d%d", &n, &q);
        for(int i = 1; i <= n; i += 1) {
            scanf("%d", &ara[ i ]);
        }
        construct();
        printf("Case %d:\n", caseno++);
        while( q-- ) {
            int op;
            scanf("%d", &op);
            if( op == 1 ) {
                scanf("%d", &pos);
                pos += 1;
                printf("%d\n", ara[ pos ]);
                val = -ara[ pos ];
                ara[ pos ] = 0;
                update();
            } else if( op == 2 ) {
                scanf("%d%d", &pos, &val);
                pos += 1;
                ara[ pos ] += val;
                update();
            } else {
                scanf("%d%d", &l, &r);
                l += 1;
                r += 1;
                printf("%d\n", query());
            }
        }
    }
    return 0;
}

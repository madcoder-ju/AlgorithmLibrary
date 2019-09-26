// Codeforces 86D
#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
 
const int N = 2e5 + 1;
int n, t, a[ N ], k[ 1000001 ];
ll res[ N ];
 
struct Query {
    int l, r, qno, box;
 
    bool operator < (const Query& q) const {
        if( q.box == box )
            return (box & 1) ? r > q.r : r < q.r;
        return box < q.box;
    }
} q[ N ];
 
ll ans;
 
void add(int x) {
    ans += (k[ x ] + k[ x ] + 1) * 1LL * x;
    k[ x ] += 1;
}
void rem(int x) {
    ans -= (k[ x ] + k[ x ] - 1) * 1LL * x;
    k[ x ] -= 1;
}
int main() {
    scanf("%d %d", &n, &t);
    for(int i = 1; i <= n; i += 1)
        scanf("%d", &a[ i ]);
 
    int squareRoot = sqrt( n );
    for(int i = 1; i <= t; i += 1) {
        scanf("%d %d", &q[ i ].l, &q[ i ].r);
        q[ i ].qno = i;
        q[ i ].box = q[ i ].l / squareRoot;
    }
 
    sort(q + 1, q + t + 1);
 
    int l = 1, r = 1;
    for(int i = 1; i <= t; i += 1) {
        while( q[ i ].l < l ) add( a[ --l ] );
        while( q[ i ].r >= r ) add( a[ r++ ] );
        while( q[ i ].l > l ) rem( a[ l++ ] );
        while( q[ i ].r + 1 < r ) rem( a[ --r ] );
        res[ q[ i ].qno ] = ans;
    }
 
    for(int i = 1; i <= t; i += 1)
        printf("%I64d\n", res[ i ]);
 
    return 0;
}

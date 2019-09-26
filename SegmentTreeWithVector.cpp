/*
 * SPOJ KQUERYO: K-Query Online
 * given an array A of n elements and q queries
 * l r k where l ^= ans, r ^= ans k ^= ans
 * ans is the previous ans initially 0
 * find the number of elements in the interval [l, r] greater than k
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 3e4 + 34;

int n, l, r, k, ara[ N ];
vector<int> tree[ N << 2 ];

void construct(int node = 1, int b = 1, int e = n) {
    if( b == e ) {
        tree[ node ].push_back(ara[ b ]); return ;
    }
    int m = (b + e) >> 1;
    construct(node << 1, b, m);
    construct(node << 1 | 1, m + 1, e);
    merge(tree[node<<1].begin(),tree[node<<1].end(),
          tree[node<<1|1].begin(),tree[node<<1|1].end(),back_inserter(tree[node]));
}
int query(int node = 1, int b = 1, int e = n) {
    if( b > e || b > r || e < l ) return 0;
    if( l <= b && e <= r) {
        int x = upper_bound(tree[node].begin(),tree[node].end(), k)-tree[node].begin();
        return tree[ node ].size() - x;
    }
    int m = (b + e) >> 1;
    return query(node << 1, b, m) + query(node << 1 | 1, m + 1, e);
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i += 1) scanf("%d", &ara[ i ]);
    
    construct();
    int q, ans = 0;
    scanf("%d", &q);
    while( q-- ) {
        scanf("%d%d%d", &l, &r, &k);
        l ^= ans; r ^= ans; k ^= ans;
        printf("%d\n", ans = query());
    }
    return 0;
}

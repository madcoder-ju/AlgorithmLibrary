/*
 * LightOJ 1082: Array Queries 
 * given an array of length n and q queries.
 * in each query find the minimum of all elements in the interval [l, r]
 */
#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;

vector<int> v, Left, Right;
int n;

void update(int t, int val) {
    int i = t;
    v[ i - 1 ] = val;
    while( i <= n ) {
        Left[ i ] = min(Left[ i ], val);
        i += (i & (-i));
    }
    i = t;
    while( i > 0 ) {
        Right[ i ] = min(Right[ i ], val);
        i -= (i & (-i));
    }
}

int query(int l, int r) {
    int ret = INF;
    int i = l;
    while( (i + (i & (-i))) <= r ) {
        ret = min(ret, Right[ i ]);
        i += (i & (-i));
    }
    ret = min(ret, v[ i - 1 ]);
    i = r;
    while( (i - (i & (-i))) >= l ) {
        ret = min(ret, Left[ i ]);
        i -= (i & (-i));
    }
    return ret;
}

int main() {
    int testcase, caseno = 1;
    scanf("%d", &testcase);
    while( testcase-- ) {
        int t, m;
        scanf("%d%d", &t, &m);

        v.clear();
        Left.clear();
        Right.clear();

        for(int i = 0; i < t; i += 1) {
            int x;
            scanf("%d", &x);
            v.push_back(x);
        }
        n = 1;
        while( (n << 1) <= t )
            n <<= 1;
        n <<= 1;
        for(int i = 0; i <= n; i += 1)
            Left.push_back(INF), Right.push_back(INF);
        for(int i = 0; i < t; i += 1) {
            update(i + 1, v[ i ]);
        }
        printf("Case %d:\n", caseno++);
        while( m-- ) {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", query(l, r));
        }
    }
    return 0;
}

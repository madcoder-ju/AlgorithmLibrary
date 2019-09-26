/*
 * Codeforces 570D
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 1;

int st[ N ], en[ N ], sub[ N ], odd[ N ], res[ N ];
int t, d[ N ], nodeAt[ N ], f[ N ][ 27 ];
string charAt;
vector<int> g[ N ];
vector<pair<int,int> > query[ N ];

void dfs(int u, int p) {
    st[ u ] = ++t;
    sub[ u ] = 1;
    d[ u ] = d[ p ] + 1;
    nodeAt[ t ] = u;
    for(int v : g[ u ]) {
        if( v == p ) continue;
        dfs(v, u);
        sub[ u ] += sub[ v ];
    }
    en[ u ] = t;
}
void dsu(int u, int p, int keep) {
    int bigson = -1;
    for(int v : g[ u ]) {
        if( v == p ) continue;
        if( bigson == -1 || sub[ bigson ] < sub[ v ] )
            bigson = v;
    }
    for(int v : g[ u ]) {
        if( v == p || v == bigson ) continue;
        dsu(v, u, 0);
    }
    if( ~bigson ) dsu(bigson, u, 1);

    int x;
    for(int v : g[ u ]) {
        if( v == p || v == bigson ) continue;
        for(int i = st[ v ]; i <= en[ v ]; i += 1) {
            x = nodeAt[ i ];
            f[ d[ x ] ][ charAt[ x - 1 ] ] += 1;
            if( f[ d[ x ] ][ charAt[ x - 1 ] ] % 2 )
                odd[ d[ x ] ] += 1;
            else odd[ d[ x ] ] -= 1;
        }
    }
    x = u;
    f[ d[ x ] ][ charAt[ x - 1 ] ] += 1;
    if( f[ d[ x ] ][ charAt[ x - 1 ] ] % 2 ) odd[ d[ x ] ] += 1;
    else odd[ d[ x ] ] -= 1;

    for(auto q : query[ u ]) {
        if( odd[ q.first ] <= 1 ) res[ q.second ] = 1;
    }

    if( keep == 0 ) {
        for(int i = st[ u ]; i <= en[ u ]; i += 1) {
            x = nodeAt[ i ];
            f[ d[ x ] ][ charAt[ x - 1 ] ] -= 1;
            if( f[ d[ x ] ][ charAt[ x - 1 ] ] % 2 )
                odd[ d[ x ] ] += 1;
            else odd[ d[ x ] ] -= 1;
        }
    }

}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for(int u, v = 2; v <= n; v += 1) {
        scanf("%d", &u);
        g[ u ].push_back( v );
        g[ v ].push_back( u );
    }
    cin >> charAt;
    dfs(1, 0);
    for(int i = 1; i <= m; i += 1) {
        int v, depth;
        scanf("%d %d", &v, &depth);
        query[ v ].push_back( {depth, i} );
    }
    dsu(1, 0, 1);
    for(int i = 1; i <= m; i += 1)
        printf("%s\n", res[ i ] ? "Yes" : "No");
    return 0;
}

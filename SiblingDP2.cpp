/*
 * LightOJ 1252
 * given an weighted tree T of n nodes. devide T into minimum number of component
 * trees such that the total cost each of those tree never exceeds k.
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 1e2 + 12, INF = 1e2 + 2;

int n, k, baby[ N ], bro[ N ], c[ N ][ N ], dp[ N ][ N ];
vector<int> g[ N ];

void tree(int u = 1, int par = 0) {
    int p = 0, flag = 1;
    for(auto v : g[ u ]) {
        if( v == par ) continue;
        if( flag ) {
            baby[ u ] = v;
            flag = 0;
        } else {
            bro[ p ] = v;
        }
        p = v;
        tree(v, u);
    }
}

/*
 * dfs(int u = 1, int par = 0, int cost = k): the state defined as the min number of
 * valid subtree that can be built including the edge from u to its parent
 */
int dfs(int u = 1, int par = 0, int cost = k) {
    if( u == -1 ) return 0;
    int &ret = dp[ u ][ cost ];
    if( ~ret ) return ret;
    ret = INF;
    
    // disconnecting the subtree rooted at baby[ u ] and passing the cost to the 
    // sibling. so, we created a new tree that's why 1 is added.
    ret = min(ret, 1 + dfs(baby[ u ], u, k) + dfs(bro[ u ], par, cost));
    cost -= c[ u ][ par ]; // remaining cost after taking the edge (u - par)
    // distributing the remaining with cost child and siblings of u 
    for(int i = 0; i <= cost; i += 1) {
        ret = min(ret, dfs(baby[ u ], u, i) + dfs(bro[ u ], par, cost - i) );
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int testcase, caseno = 1;
    cin >> testcase;

    while( testcase-- ) {
        cin >> n >> k;

        for(int i = 0; i <= n; i += 1) {
            g[ i ].clear();
            baby[ i ] = bro[ i ] = -1;
            for(int j = 0; j <= k; j += 1) {
                dp[ i ][ j ] = -1;
            }
        }

        int edge = n - 1;
        while( edge-- ) {
            int u, v, w;
            cin >> u >> v >> w;
            g[ u ].push_back( v );
            g[ v ].push_back( u );
            c[ u ][ v ] = c[ v ][ u ] = w;
        }
        c[ 1 ][ 0 ] = c[ 0 ][ 1 ] = INF;
        tree();
        int ans = dfs();
        cout << "Case " << caseno++ << ": " << ans << '\n';
    }
    return 0;
}

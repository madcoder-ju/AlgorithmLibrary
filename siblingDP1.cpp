/*
 * CodeMarshal DUET IUPC 2019 H: Skill Matching
 * given a weighted tree T of n nodes and a value m. each node has a value 
 * 1 <= a[ i ] <= 10. find a minimum subtree of T that contains each number 
 * between 1 to m at least once. The ans is (n - minimum subtree size).
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 1050;

int n, m, a[ N ], dp[ N ][ N ], baby[ N ], bro[ N ];
vector<int> g[ N ];

// tree(int u = 1, int par = 0): makes a sibling tree
void tree(int u = 1, int par = 0) {
    int p = 0, flag = 1;
    for(int v : g[ u ]) {
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
 * dfs(int u, int par, int mask): gives the ans considering only the tree rooted at u
 */ 
int dfs(int u, int par, int mask) {
    if( mask == 0 ) return 0;
    if( u == -1 ) return N;
    int &ret = dp[ u ][ mask ];
    if( ~ret ) return ret;
    ret = N;
    int msk = mask;
    if( msk & (1 << a[ u ]) )
        msk = mask ^ (1 << a[ u ]);
    
    if( mask == ((1 << m) - 1))
        ret = 1 + dfs(baby[ u ], u, msk); // only calling the initial root's child
    else {
        ret = min(ret, dfs(bro[ u ], par, mask)); //all mask passing to sibling of u
        ret = min(ret, 1 + dfs(bro[ u ], par, msk)); //taken u and pass remaining mask
        for(int k = msk; k > 0; k = msk & (k - 1))
            // taking u and distributing masks to child and sibling
            ret = min(ret, 1 + dfs(baby[ u ], u, k) + dfs(bro[ u ], par, k ^ msk));
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
        cin >> n >> m;
        for(int i = 1; i <= n; i += 1) {
            cin >> a[ i ];
            a[ i ]--;
        }

        for(int i = 1; i <= n; i += 1) {
            g[ i ].clear();
            baby[ i ] = bro[ i ] = -1;
            for(int k = 0; k <= (1 << m) - 1; k += 1)
                dp[ i ][ k ] = -1;
        }

        for(int i = 1; i < n; i += 1) {
            int u, v;
            cin >> u >> v;
            g[ u ].push_back( v );
            g[ v ].push_back( u );
        }

        tree();
        int res = N;
        // minimizing the ans taking all nodes as a root
        for(int i = 1; i <= n; i += 1) {
            res = min(res, dfs(i, i, (1 << m) - 1));
        }
        cout << "Case " << caseno++ << ": " << n - res << '\n';
    }
    return 0;
}

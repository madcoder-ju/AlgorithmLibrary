#include <bits/stdc++.h>

using namespace std;

struct matching {

  static const int N = 1 << 17, INF = 1 << 30;
  int n, dis[ N ], match[ N ];
  vector<int> g[ N ];

  void reset(int node) {
    n = node;
    for(int i = 0; i < N; i += 1) {
      g[ i ].clear();
      match[ i ] = 0;
    }
  }

  bool bfs() {
    queue<int>Q;
    for(int i = 1; i <= n; i += 1) {
      if( !match[ i ] ) dis[ i ] = 0, Q.push( i );
      else dis[ i ] = INF;
    }

    dis[ 0 ] = INF;
    while( !Q.empty() ) {
      int u = Q.front(); Q.pop();
      if( u ) {
        for(int i = 0; i < g[ u ].size(); i += 1) {
          int v = g[ u ][ i ];
          if( dis[ match[ v ] ] == INF ) {
            dis[ match[ v ] ] = dis[ u ] + 1;
            Q.push( match[ v ] );
          }
        }
      }
    }
    return dis[ 0 ] != INF;
  }

  bool dfs(int u) {
    if( u ) {
      for(int i = 0; i < g[ u ].size(); i += 1) {
        int v = g[ u ][ i ];
        if( dis[ match[ v ] ] == dis[ u ] + 1 ) {
          if( dfs( match[ v ] ) ) {
            match[ v ] = u;
            match[ u ] = v;
            return true;
          }
        }
      }
      dis[ u ] = INF;
      return false;
    }
    return true;
  }

  int maxMatching() {
    int matches = 0;

    while( bfs() == true ) {
      for(int i = 1; i <= n; i += 1) {
        if( !match[ i ] && dfs( i ) ) matches += 1;
      }
    }
    return matches;
  }
} HC;

int a[ 200 ], b[ 200 ];

int main() {
    int cases, caseno = 1;
    scanf("%d", &cases);

    while( cases-- ) {
        int n, m;
        scanf("%d", &n);
        for(int i = 1; i <= n; i += 1) {
          scanf("%d", &a[ i ]);
        }
        scanf("%d", &m);
        for(int i = 1; i <= m; i += 1) {
          scanf("%d", &b[ i ]);
        }

        HC.reset( n );

        for(int i = 1; i <= n; i += 1) {
            for(int j = 1; j <= m; j += 1) {
                if( b[ j ] % a[ i ] == 0 ){
                  HC.g[ i ].push_back( n + j );
                  HC.g[ n + j ].push_back( i );
                }
            }
        }
        printf("Case %d: %d\n", caseno++, HC.maxMatching() );
    }
    return 0;
}

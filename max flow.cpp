// LightOJ 1155
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e8;

struct MaxFlow {

    struct EDGE {
        int v, f = 0, c, r;
        EDGE(int _v, int _c, int _r) {
            v = _v;
            c = _c;
            r = _r;
        }
    };

    int n, s, t;
    vector<int> lev, ptr;
    vector<vector<EDGE> > G;


    MaxFlow(int nodes, int source, int sink) {
        n = nodes;
        s = source;
        t = sink;
        lev.resize( n );
        G.resize( n );
        ptr.resize( n );
    }

    void createEdge(int u, int v, int c) {
        G[ u ].push_back( EDGE(v, c, G[ v ].size()));
        G[ v ].push_back( EDGE(u, 0, G[ u ].size() - 1));
    }

    bool bfs() {
        fill(lev.begin(), lev.end(), -1);
        queue<int> Q;
        Q.push(s);
        lev[ s ] = 0;

        while( !Q.empty() ) {
            int u = Q.front();
            Q.pop();
            for(int i = 0; i < (int)G[ u ].size(); i += 1) {
                EDGE &e = G[ u ][ i ];
                if( lev[ e.v ] == -1 && e.f < e.c ) {
                    lev[ e.v ] = lev[ u ] + 1;
                    Q.push( e.v );
                }
            }
        }
        return ~lev[ t ];
    }

    int dfs(int u, int flow) {
        if( !flow || u == t ) return flow;
        for(int &i = ptr[ u ]; i < (int)G[ u ].size(); i += 1) {
            EDGE &e = G[ u ][ i ];
            if( lev[ e.v ] == lev[ u ] + 1 && e.f < e.c ) {
                int x = dfs(e.v, min(flow, e.c - e.f));
                if( x > 0 ) {
                    e.f += x;
                    G[ e.v ][ e.r ].f -= x;
                    return x;
                }
            }
        }
        return 0;
    }

    int getMaxFlow() {
        int ret = 0;
        while( bfs() ) {
            fill(ptr.begin(), ptr.end(), 0);
            while( int x = dfs(s, INF) ) ret += x;
        }
        return ret;
    }
};

int main() {
    int testcase;
    scanf("%d", &testcase);

    int caseno = 1;
    while( testcase-- ) {
        int n;
        scanf("%d", &n);

        MaxFlow F( n + n + 2, 0, n + n + 1 );

        for(int i = 1; i <= n; i += 1) {
            int v;
            scanf("%d", &v);
            F.createEdge(i, i + n, v);
        }

        int m;
        scanf("%d", &m);

        while( m-- ) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            F.createEdge(u + n, v, c);
        }

        int b, d;
        scanf("%d %d", &b, &d);

        while( b-- ) {
            int u;
            scanf("%d", &u);
            F.createEdge(0, u, INF);
        }

        while( d-- ) {
            int u;
            scanf("%d", &u);
            F.createEdge(u + n, n + n + 1, INF);
        }

        int ans = 0;
        ans = F.getMaxFlow();
        printf("Case %d: %d\n", caseno++, ans);
    }
    return 0;
}

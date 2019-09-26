/*
 * Perform Q operations on a set S( initially empty )
 *  I x: insert x into s if x is not in S
 *  D x: delete x if it is in S
 *  K x: find kth smallest element
 *  C x: count no. of elements less than x
 */
#include <bits/stdc++.h>

using namespace std;

using PII = pair<int,int>;

const int N = 3e5;
int root, node, lson[ N ], rson[ N ], data[ N ], prior[ N ], sz[ N ], lazy[ N ];

mt19937 Ran(time(0));

/*
 * reset(): initializes data
 */
void reset( ) {
    root = node = 0;
}

/*
 * createNode(int v): creates a node of value v
 */
int createNode( int v ) {
    node += 1;
    data[ node ] = v;
    lson[ node ] = rson[ node ] = 0;
    prior[ node ] = rand();
    sz[ node ] = 1;
    return node;
}

/*
 * update(int node): updates the node information i.e size, sum etc.
 */
void update(int node) {
    if( node ) {
        sz[ node ] = sz[ lson[ node ] ] + sz[ rson[ node ] ] + 1;
    }
}

/*
 * propagate(int node): propagates node as segment tree
 */
void propagate(int node) {
    if( node && lazy[ node ] ) {

    }
}

/*
 * join(int l, int r): join BST of root l and BST of root r
 */
int join(int l,int r) {
    propagate(l);
    propagate(r);
    if( !l || !r ) return l ? l : r;
    if( prior[ l ] >= prior[ r ] ) {
        rson[ l ] = join( rson[ l ], r );
        update( l );
        return l;
    } else {
        lson[ r ] = join( l, lson[ r ] );
        update( r );
        return r;
    }
}

/*
 * splitByValue(int node, int v): splits the BST into two BSTs.
 * The first one contains nodes of values <= v
 * The second one contains nodes of values greater than v
 */
PII splitByValue( int node, int v ) {
    if( !node ) return {0, 0};
    if( data[ node ] <= v ) {
        PII ret = splitByValue( rson[ node ], v );
        rson[ node ] = ret.first;
        update( node );
        return { node, ret.second };
    } else {
        PII ret = splitByValue( lson[ node ], v );
        lson[ node ] = ret.second;
        update( node );
        return { ret.first, node };
    }
}

/*
 * splitBySize(int node, int v): splits the BST into two BSTs.
 * The first one contains total nodes of v
 * The second one contains rest of the nodes
 */
PII splitBySize(int node,int s) {
    if( !node ) return {0, 0};
    if( sz[ lson[ node ] ] < s ) {
        PII ret = splitBySize( rson[ node ], s - sz[ lson[ node ] ] - 1 );
        rson[ node ] = ret.first;
        update( node );
        return { node, ret.second };
    } else {
        PII ret = splitBySize( lson[ node ], s );
        lson[ node ] = ret.second;
        update( node );
        return { ret.first, node };
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int operation;
    cin >> operation;

    while( operation-- ) {
        char type;
        int var;
        cin >> type >> var;
        if( type == 'I' ) {
            PII a = splitByValue( root, var );
            PII b = splitByValue( a.first, var - 1 );
            root = join( join( b.first, createNode( var ) ), a.second );
        } else if( type == 'D' ) {
            PII a = splitByValue( root, var );
            PII b = splitByValue( a.first, var - 1);
            root = join( b.first, a.second );
        } else if( type == 'C' ) {
            PII a = splitByValue( root, var - 1 );
            cout << sz[ a.first ] << '\n';
            root = join( a.first, a.second );
        } else {
            if( sz[ root ] < var ) {
                cout << "invalid\n";
                continue;
            }
            PII a = splitBySize( root, var - 1 );
            PII b = splitBySize( a.second, 1);
            cout << data[ b.first ] << '\n';
            root = join( a.first, join( b.first, b.second ) );
        }
    }
    return 0;
}

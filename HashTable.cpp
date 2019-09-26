/*
 * find the longest common substring of string A and B
 */
#include <bits/stdc++.h>

using namespace std;

using ll = unsigned long long;

const int N = 1e6 + 1;
const ll mod = ((ll)1 << 61) - 1;
const ll base = 257;

ll pw[ N ];

// mul(ll a, ll b): calculates (a * b) % mod 
ll mul(ll a, ll b) {
    ll l1 = (uint32_t)a, h1 = a >> 32;
    ll l2 = (uint32_t)b, h2 = b >> 32;
    ll l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    ll ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod) + (ret >> 61);
    ret = (ret & mod) + (ret >> 61);
    return ret - 1;
}

struct PolyHash {

    vector<ll> h;

    PolyHash(string &s) {
        ll x = 0, y = 0;
        for(char ch : s) {
            x = ( mul(x, base) + ch ) % mod;
            h.push_back(x);
        }
    }
    ll getHash(int l, int r) {
        ll x = h[ r ];
        if( l == 0 ) return x;
        x = (x - mul(h[ l - 1 ], pw[ r - l + 1 ]) + mod) % mod;
        return x;
    }
};

// open address hash table structure
struct HashTable {
    static const ll step = 1122357, n = 2000177;
    array<ll, n> data;

    HashTable() {
        for(auto& it : data) it = 0;
    }
    
    // getPos(ll val): gives the hash value of val
    int getPos(ll val) const {
        return (val + step) % n;
    }
    
    // insert(ll val)L inserts val into hash table
    void insert(ll val) {
        int x = getPos(val);
        while( true ) {
            if( data[ x ] == val ) return ;
            if( data[ x ] == 0 ) {
                data[ x ] = val;
                return ;
            }
            x = (x + step) % n;
        }
    }
    
    // find(ll val): true if val is in hash table
    bool find(ll val) {
        int x = getPos(val);
        while( true ) {
            if( data[ x ] == val ) return 1;
            if( data[ x ] == 0 ) return 0;
            x = (x + step) % n;
        }
    }
};
int main() {
    pw[ 0 ] = 1;
    for(int i = 1; i < N; i += 1) {
        pw[ i ] = mul(pw[ i - 1 ], base);
    }

    string a, b;
    char buf[ N ];
    scanf("%1000000s", buf); a = buf;
    scanf("%1000000s", buf); b = buf;

    PolyHash A(a), B(b);
    
    // binary searching the ans over length
    int lo = 0, hi = min((int)a.size(), (int)b.size()) + 1;
    while( hi - lo > 1 ) {
        int mid = (hi + lo) >> 1;

        HashTable vis;
        
        // stores of hash values of substrings of length mid of A into hash table
        for(int i = 0; i + mid - 1 < (int)a.size(); i += 1) {
            auto x = A.getHash(i, i + mid - 1);
            vis.insert(x);
        }

        bool flag = 0;
        
        // checks if any substring of length mid of B exists in the hash table
        for(int i = 0; i + mid - 1 < (int)b.size(); i += 1) {
            if( vis.find(B.getHash(i, i + mid - 1)) ) {
                flag = 1;
                break;
            }
        }

        if( flag ) lo = mid;
        else hi = mid;
    }

    cout << lo << '\n';
    return 0;
}

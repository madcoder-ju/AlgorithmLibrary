+------------------+
|   Bitwise Seive  |
+------------------+

vector<int> prime;
bitset<N> vis;

void sieve() {
    vis[0] = 0;
    for(int i = 3; i * i < N; i += 2)
        if( vis[ i ] == 0 )
            for(int j = i * i, k = i << 1; j < N; j += k)
                vis[ j ] = 1;
    prime.push_back(2);
    for(int i = 3; i < N; i += 2)
        if(!vis[ i ]) prime.push_back(i);
}

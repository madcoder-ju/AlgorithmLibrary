/************ Seive **************/
int IsPrime[N+2];vector<int>Prime;
void Seive(int n)
{
  Prime.push_back(2);IsPrime[1]=1;
  for(int i=4;i<=n;i+=2)IsPrime[i]=1;
  int sq=sqrt(n+1);
  for(int i=3;i<=n;i+=2)
  {
    if(IsPrime[i])continue;Prime.push_back(i);
    if(i>sq)continue;
    for(int j=i*i;j<=n;j+=2*i)
      IsPrime[j]=1;
  }
}
///////////////////////////////////
+------------------+
|   Bitwise Seive  |
+------------------+

const ll N = 1e8 + 1;
ll p, prime[ 5761461 ];
bitset<N> vis;

void sieve() {
    vis[0] = 0;
    for(unsigned i = 3; i < 10000; i += 2)
        if( vis[ i ] == 0 )
            for(unsigned j = i * i, k = i << 1; j < N; j += k)
                vis[ j ] = 1;
    p = 0;
    prime[ p++ ] = 2;
    for(unsigned i = 3; i < N; i += 2)
        if(!vis[ i ])
        	prime[ p++ ] = i;
}

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

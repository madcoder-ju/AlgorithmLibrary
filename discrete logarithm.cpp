/************ Baby Step Giant Step ************/
long BsGs(long a,long b,long m)
{
  int n=sqrt(m+1);long an=1;
  for(int i=0;i<n;i++)an=(an*a)%m;
  map<int,int>mp;//unoedered is good choice
  long cur=an;
  for(int i=1;i<=n;i++)
  {
    if(!mp.count(cur))
      mp[cur]=i;
    cur=(cur*an)%m;
  }
  cur=b;
  for(int i=0;i<=n;i++)
  {
    if(mp.count(cur))
    {
      long ans=mp[cur]*n-i;
      if(ans<m)return ans;
      //modify for largest/smallest solution
    }
    cur=(cur*a)%m;
  }
  return -1;//no solution
}
//Finds such k that a^k(mod m)=b;
//a and m have to be relatively prime
////////////////////////////////////////////////////


/************* Discrete Root **************/
long Bigmod(long b,long p,long mod)
{
  long ret=1LL;
  while(p)
  {
    if(p%2)ret=(ret*b)%mod;
    b=(b*b)%mod;p/=2;
  }
  return ret;
}
int Primitive_Root(int p)//p is prime
{
  vector<int>fac;int phi=p-1;
  int n=phi;int sq=sqrt(n+1);
  for(int i=2;i<=sq;i++)
  {
    if(n%i==0)fac.push_back(i);
    while(n%i==0)n/=i;
  }
  if(n>1)fac.push_back(n);
  for(int i=2;i<=p;i++)
  {
    bool ok=true;
    for(auto x:fac)
    {
      if(Bigmod(i,phi/x,p)==1)
      {
        ok=false;break;
      }
    }
    if(ok)return i;
  }
  return -1;
  /*all number from 1 to p-1 can be 
  represented by power of primitive root*/
}
long BsGs(long a,long b,long m)
{
  int n=sqrt(m+1);long an=1;
  for(int i=0;i<n;i++)an=(an*a)%m;
  map<int,int>mp;//unordered is good choice
  long cur=an;
  for(int i=1;i<=n;i++)
  {
    if(!mp.count(cur))
      mp[cur]=i;
    cur=(cur*an)%m;
  }
  cur=b;long mn=1e18;int f=0;
  for(int i=0;i<=n;i++)
  {
    if(mp.count(cur))
    {
      long ans=mp[cur]*n-i;
      if(ans<m)mn=min(mn,ans),f=1;
      //modify for largest/smallest solution
    }
    cur=(cur*a)%m;
  }
  if(!f)return -1;
  else return mn;
}
int Discrete_Root(int k,int b,int p)
{
  int g=Primitive_Root(p);
  int pw=BsGs(Bigmod(g,k,p),b,p);
  if(pw==-1)return -1;
  int a=Bigmod(g,pw,p);
  return a;
  /*int delta=(p-1)/__gcd(k,p-1);
  vector<int>ans;
  for(int cur=a%delta;cur<p-1;cur+=delta)
  ans.push_back(Bigmod(g,cur,p));
  sort(ans.begin(), ans.end());
  for(auto x:ans)cout<<x<<endl;*/
}
//Finds such a that (a^k)%p=b;
////////////////////////////////////////////

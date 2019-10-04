/*************** Bigmod *******************/

//mod<=1e9
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

//mod>1e9 //Supports __int128
long Bigmod(__int128 b,long p,__int128 mod)
{
  __int128 ret=1;
  while(p)
  {
    if(p%2)ret=(ret*b)%mod;
    b=(b*b)%mod;p/=2;
  }
  return ret;
}

//mod>1e9 complexity log^2
long Multiply(long a,long b,long mod)
{
  if(a>b)swap(a,b);long ret=0;
  while(a)
  {
    if(a%2)ret=(ret+b)%mod;
    b=(b+b)%mod;a/=2;
  }
  return ret;
}
long Bigmod(long b,long p,long mod)
{
  long ret=1;
  while(p)
  {
    if(p%2)ret=Multiply(ret,b,mod);
    b=Multiply(b,b,mod);p/=2;
  }
  return ret;
}

///////////////////////////////////////////

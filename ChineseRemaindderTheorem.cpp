/*
solves the congruence equations
  x=r1(mod m1)
  x=r2(mod m3)
  x=r3(mod m3)
  x=r3(mod m2)
finds minimum x modulo m
rr is the remainder array
mm is the modulo array
*/
int exgcd(int a,int b,int &x,int &y)
{
  if(!b){x=1,y=0;return a;}
  int x1,y1;
  int g=exgcd(b,a%b,x1,y1);
  x=y1;
  y=x1-((int)(a/b))*y1;
  return g;
}
int crt(vector<int>rr,vector<int>mm)
{
  int r=rr[0],m=mm[0],f=0,n=rr.size();
  for(int i=1;i<n;i++)
  {
    int x,y,g;g=exgcd(m,mm[i],x,y);
    if((rr[i]-r)%g!=0)return -1;
    int md=(m/g)*mm[i];
    r=r+((((rr[i]-r)/g*x)%mm[i])*m)%md;
    r=(r+md)%md;m=md;
  }
  return r;
}

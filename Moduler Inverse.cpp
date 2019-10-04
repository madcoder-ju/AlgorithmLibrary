long inv(long a,long b)
{
 return 1<a?b-inv(b%a,a)*b/a:1;
}

void modular_inverse(int m)
{
  inv[1]=1;
  for(int i=2;i<m;i++)
    inv[i]=(m-(m/i)*inv[m%i]%m)%m;
}

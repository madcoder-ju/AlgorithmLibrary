/*********** Eular Phi **********/
int Phi[N+2];
void PHI(int n)
{
  for(int i=1;i<=n;i++)
  {
    Phi[i]+=i;
    for(int j=i+i;j<=n;j+=i)
      Phi[j]-=Phi[i];
  }
}
//n*((p-1)/p) such that p|n
//////////////////////////////////

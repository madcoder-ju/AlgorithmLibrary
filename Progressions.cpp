/**************** Progressions *******************/
long AP(long n,long first,long df)
{
  long ret=2*first+(n-1)*df;
  return (ret*n)/2;
}
long GP(long n,long first,long fc)
{
  long ret=first*(pow(fc,n)-1);
  return ret/(fc-1);
}
/////////////////////////////////////////////////

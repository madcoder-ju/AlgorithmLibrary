/********** Random Generator **********/
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//mt19937 Return unsigned int;
//mt19937_64 Return unsigned long int
//call rng() for random
//shuffle(v.begin(),v.end(),rng);
unsigned int Rand(unsigned int lo,unsigned int hi)
{
  unsigned int df=(hi-lo+1);
  return lo+rng()%df;
}
///////////////////////////////////////

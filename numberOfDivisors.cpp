ll numberOfDivisors(ll n) {
	ll ans = 1;
	for(auto i : prime) {
        if( i * i * 1LL > n ) break;
        if( n % i == 0 ) {
        	int c = 0;
            while( n % i == 0 ) {
                n /= i;
                c += 1;
            }
            ans *= (c + 1);
        }
    }
    if( n > 1 ) ans *= 2;
	return ans;
}

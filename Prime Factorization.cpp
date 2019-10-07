sqrt(n) solution:
-----------------

void primeFactorizer(int n, vector<int> &vec) {
    for(int i = 2; i * i <= n; i += 1) {
        if( n % i == 0 ) {
            while( n % i == 0 ) {
                n /= i;
            }
            vec.push_back(i); 
        }
    }
    if( n > 1 ) {
        vec.push_back(n);
    }
}


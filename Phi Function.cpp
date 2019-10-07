source code:
------------

int phi[ N ];
void eulerPhi() {
    for(int i = 1; i < N; i += 1) {
        phi[ i ] += i;
        for(int j = i + i; j < N; j += i)
            phi[ j ] -= phi[ i ];
    }
}

/*
Informations:
-------------

* learn: https://brilliant.org/wiki/eulers-totient-function/
* sum of numbers less than N those are coprimes to N: N * PHI(N) / 2
* phi(a*b) = phi(a)*phi(b)*(d/(phi(a,b)) where d = gcd(a, b)
* so if gcd(a, b) = 1, then phi(a*b)=phi(a)*phi(b)
* if p is a prime, 
* then phi(p) = p - 1, phi(p^i) = phi(p^(i-1))*p
* sum of divisors: ∑ ϕ(d) = n where d divides n
* n*((p-1)/p) such that p|n
*/

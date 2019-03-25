// a primitive root modulo n is any number g such that any c coprime to n is congruent to a power of g modulo n.
bool exists_root(ll n){
    if(n == 1 || n == 2 || n == 4) return true;
    if(n % 2 == 0) n /= 2;
    if(n % 2 == 0) return false;
    // test if n is a power of only one prime
    for(ll i = 3; i * i <= n; i += 2) if(n % i == 0){
        while(n % i == 0) n /= i;
        return n == 1;
    }
    return true;
}
ll primitive_root(ll n){
    if(n == 1 || n == 2 || n == 4) return n - 1;
    if(not exists_root(n)) return -1;
    ll x = phi(n);
    auto pr = factorize(x);
    auto check = [x, n, pr](ll m){
        for(ll p : pr) if(fexp(m, x / p, n) == 1)
            return false;
        return true;
    };
    for(ll m = 2; ; m++) if(__gcd(m, n) == 1)
        if(check(m)) return m;
}

// Let's denote R(n) as the set of primitive roots modulo n, p is prime
// g \in R(p) => (pow(g, p-1, p * p) == 1 ? g+p : g) \in R(pow(p, k)), for all k > 1
// g in R(pow(p, k)) => (g % 2 == 1 ? g : g + pow(p, k)) \in R(2*pow(p, k))


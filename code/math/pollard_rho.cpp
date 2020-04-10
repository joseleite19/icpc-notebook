ll rho(ll n){
	if(n % 2 == 0) return 2;
	ll d, c, x, y, prod;
	do{
		c = llrand(1, n - 1);
		x = llrand(1, n - 1);
		y = x;
		prod = 1;
		for(int i = 0; i < 40; i++) {
			x = add(mul(x, x, n), c, n);
			y = add(mul(y, y, n), c, n);
			y = add(mul(y, y, n), c, n);
			prod = mul(prod, abs(x - y), n) ?: prod;
		}
		d = __gcd(prod, n);
	} while(d == 1);
	return d;
}

ll pollard_rho(ll n){
	ll x, c, y, d, k;
	int i;
	do{
		i = 1;
		x = llrand(1, n-1), c = llrand(1, n-1);
		y = x, k = 4;
		do{
			if(++i == k) y = x, k *= 2;
			x = add(mul(x, x, n), c, n);
			d = __gcd(abs(x - y), n);
		}while(d == 1);
	}while(d == n);
	return d;
}
void factorize(ll val, map<ll, int> &fac){
	if(rabin(val)) fac[ val ]++;
	else{
		ll d = pollard_rho(val);
		factorize(d, fac);
		factorize(val / d, fac);
	}
}
map<ll, int> factor(ll val){
	map<ll, int> fac;
	if(val > 1) factorize(val, fac);
	return fac;
}

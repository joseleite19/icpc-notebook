ll rho(ll n){
	if(n % 2 == 0) return 2;

	ll d, c = llrand() % n, x = llrand() % n, y = x;
	do{
		x = add(mul(x, x, n), c, n);
		y = add(mul(y, y, n), c, n);
		y = add(mul(y, y, n), c, n);
		d = __gcd(abs(x - y), n);
	}while(d == 1);
	return d;
}


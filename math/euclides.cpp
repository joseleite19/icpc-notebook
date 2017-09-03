// a*x + b*y = gcd(a, b),  <gcd, <x, y>>
typedef tuple<int, int, int> tiii;
tiii euclidesExt(int a, int b) {
	if(b == 0) return tiii(a, 1, 0);
	tiii ret = euclidesExt(b, a % b);

	int q, w, e;
	tie(q, w, e) = ret;

	get<1>(ret) = e;
	get<2>(ret) = w - e*(a / b);

	return ret;
}

// a*b = 1 (mod c) <-> a*b + c*k = 1
int invmult(int a, int b){
	return (get<1>(euclidesExt(a, b)) + b) % b;
}

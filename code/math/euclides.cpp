// a*x + b*y = gcd(a, b),  <gcd, x, y>
tuple<int, int, int> euclidesExt(int a, int b) {
	if(b == 0) return make_tuple(a, 1, 0);
	int q, w, e;
	tie(q, w, e) = euclidesExt(b, a % b);
	return make_tuple(q, e, w - e * (a / b));
}

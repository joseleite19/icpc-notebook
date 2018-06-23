// typedef complex<double> base;
struct base{
	double r, i;
	base(double r = 0, double i = 0) : r(r), i(i) {}
	base operator*(const base &o){
		return base(r*o.r - i*o.i, r*o.i + o.r*i);
	}
	
	base& operator*=(const base &o){
		double newr = r*o.r - i*o.i, newi = r*o.i + o.r*i;
		r = newr, i = newi;
		return *this;
	}
	
	base& operator+=(const base &o){
		r += o.r, i += o.i;
		return *this;
	}

	base& operator/=(const double &o){
		r /= o, i /= o;
		return *this;
	}
	
	base& operator-=(const base &o){
		r -= o.r, i -= o.i;
		return *this;
	}

	base operator+(const base &o){
		return base(r + o.r, i + o.i);
	}

	base operator-(const base &o){
		return base(r - o.r, i - o.i);
	}	
};

double PI = acos(-1);
 
void fft(vector<base> &a, bool inv){
	int n = (int)a.size();
 
	for(int i = 1, j = 0; i < n; i++){
		int bit = n >> 1;
		for(; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if(i < j)
			swap(a[i], a[j]);
	}
 
	for(int len = 2; len <= n; len <<= 1) {
		double ang = 2*PI/len * (inv ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len){
			base w(1);
			for (int j = 0; j < len/2; j++){
				base u = a[i+j], v = a[i+j+len/2] * w;
				a[i+j] = u + v;
				a[i+j+len/2] = u - v;
				w *= wlen;
			}
		}
	}
	if(inv)
		for(int i = 0; i < n; i++)
			a[i] /= n;
}
void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res){
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	size_t n = 1;
	while(n < a.size()) n <<= 1;
	while(n < b.size()) n <<= 1;
	n <<= 1;
	fa.resize(n), fb.resize(n);

	fft(fa, false), fft (fb, false);
	for(size_t i = 0; i < n; i++)
		fa[i] *= fb[i];
	fft(fa, true);

	res.resize (n);
	for(size_t i = 0; i < n; ++i)
		res[i] = int(fa[i].real() + 0.5);
}
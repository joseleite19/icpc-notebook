#include <bits/stdc++.h>

#define ff first
#define ss second
#define mp make_pair

using namespace std;

int pot(int base, int exp, int mod){
	int resp = 1;

	while(exp){
		if(exp & 1)
			resp = ((long long)resp * base) % mod;
		base = ((long long)base * base) % mod;

		exp >>= 1;
	}
	return resp;
}

int totiente(int n){
	long long i;
	int ans = 1, tmp;
	for(i = 2; i*i <= n; i++){
		if(n % i == 0){
			tmp = 0;
			ans *= i-1;
			while(n % i == 0){ n /= i; tmp++; }
			ans *= pot(i, tmp-1, n);
		}
	}

	if(n > 1){
		ans *= n-1;
	}

	return ans;
}

pair<int, pair<int, int> > euclidesExt(int  a, int b) {
	if(b == 0) return mp(a, mp(1, 0));

	pair<int, pair<int, int> > ret = euclidesExt(b, a%b);
	pair<int, int> tmp = ret.ss;

	ret.ss.ff = tmp.ss;
	ret.ss.ss = tmp.ff - tmp.ss*(a/b);

	return ret;
}

// a*b = 1 (mod c)   <->    a*b + c*k = 1
int invmult(int a, int b){
	return (euclidesExt(a, b).ss.ff + b) % b;
}

int main(){
	int n, e, c, tot;
	
	scanf("%d %d %d", &n, &e, &c);

	tot = totiente(n);

	int d = invmult(e, tot);

	int m = pot(c, d, n);

	printf("%d\n", m);

	return 0;
}


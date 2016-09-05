#include <bits/stdc++.h>

#define oo 1000000000000000000

using namespace std;

string s[100005];
string r[100005];
int n, c[100005];

long long dp[100005][2];
bool mark[100005][2];

long long f(int x, int rev){
	if(mark[x][rev]) return dp[x][rev];
	mark[x][rev] = 1;

	if(x == n) return 0;

	if(x == 0) return min(c[x] + f(x+1, 1), f(x+1, 0));

	bool canforward = false, canreverse = false;
	long long ans = oo;

	if(rev){
		if(s[x] >= r[x-1]) canforward = true;
		if(r[x] >= r[x-1]) canreverse = true;
	}
	else{
		if(s[x] >= s[x-1]) canforward = true;
		if(r[x] >= s[x-1]) canreverse = true;
	}
	
	if(canforward) ans = min(ans, f(x+1, 0));
	if(canreverse) ans = min(ans, c[x]+f(x+1, 1));

	return dp[x][rev] = ans;
}

int main(){

	scanf("%d", &n);

	for(int i = 0; i < n; i++)
		scanf("%d", c+i);

	for(int i = 0; i < n; i++){
		cin >> s[i];
		r[i] = s[i];
		reverse(r[i].begin(), r[i].end());
	}

	long long ret = f(0, 0);
	printf("%lld\n", ret == oo ? -1 : ret);

	return 0;
}
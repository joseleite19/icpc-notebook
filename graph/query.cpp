#include <bits/stdc++.h>
 
using namespace std;
#define MAXL 18
#define mp make_pair
#define ff first
#define ss second
 
typedef long long ll;
typedef pair<int,int> ii;
 
int p[10100], L[10100], vis[10100], dp[10100][MAXL], pw[10100], dp2[10100][MAXL];
 
vector<vector<ii> > g;
 
void dfs(int u){
	vis[u] = 1;
 
	for(ii &v : g[u]){
		if(!vis[v.ff]){
			p[v.ff] = u;
			L[v.ff] = L[u]+1;
			pw[v.ff] = v.ss;
			dfs(v.ff);
		}
	}
}
 
int f(int u, int j){
	if(j == 0) return p[u];
	if(dp[u][j] != -1) return dp[u][j];
	return dp[u][j] = f(f(u, j-1), j-1);
}

ll h(int u, int j){
	if(j == 0) return pw[u];
	if(dp2[u][j] != -1) return dp2[u][j];
	return dp2[u][j] = h(u, j-1) + h(f(u, j-1), j-1);
}
 
int LCA(int u, int v){
	if(L[u] < L[v]) swap(u, v);
 
	for(int i = MAXL-1; i >= 0; i--)
		if(L[ f(u, i) ] >= L[v])
			u = f(u, i);
 
	if(u == v) return v;
 
	for(int i = MAXL-1; i >= 0; i--)
		if(f(u, i) != f(v, i))
			u = f(u, i), v = f(v, i);
 
	return p[u];
}
 
 
long long DIST(int u, int v){
	if(L[u] < L[v]) swap(u, v);
 
	ll ans = 0;
 
	for(int i = MAXL-1; i >= 0; i--)
		if(L[ f(u, i) ] >= L[v])
			ans += h(u, i), u = f(u, i);
 
	if(u == v) return ans;
 
	for(int i = MAXL-1; i >= 0; i--)
		if(f(u, i) != f(v, i))
			ans += h(u, i) + h(v, i), u = f(u, i), v = f(v, i);
 
	ans += pw[u] + pw[v];
	return ans;
}
 
int KTH(int a, int b, int c){
	int lca = LCA(a, b);
	int u = a, v = b;
	if(c > L[a] - L[lca] + 1){
		c -= L[a] - L[lca] + 1;
		for(int i = MAXL-1; i >= 0; i--)
			if(L[ f(v, i) ] - L[lca] >= c)
				v = f(v, i);
		return v;
	}
	else{
		for(int i = MAXL-1; i >= 0; i--)
			if(L[a] - L[ f(u, i) ] + 1 <= c)
				u = f(u, i);
		return u;
 
	}
	return 0;
}
 
int main(){
	int n, T, a, b, c;
 
	scanf("%d", &T);
 
	for(int t = 1; t <= T; t++){
		scanf("%d", &n);
		g.assign(n+1, vector<ii>());
 
		for(int i = 1; i < n; i++){
			scanf("%d %d %d", &a, &b, &c);
			g[a].push_back(ii(b, c));
			g[b].push_back(ii(a, c));
		}
 
		memset(vis, 0, sizeof vis);
		memset(p, 0, sizeof p);
		memset(L, 0, sizeof L);
		L[1] = 0;
		p[1] = 1;
		dfs(1);
 
		memset(dp, -1, sizeof dp);
		memset(dp2, -1, sizeof dp2);
 
		char s[10];
 
		while(scanf(" %s", s) == 1 && s[1] != 'O'){
			if(s[0] == 'D'){
				scanf("%d %d", &a, &b);
				printf("%lld\n", DIST(a, b));
			}
			else{
				scanf("%d %d %d", &a, &b, &c);
				printf("%d\n", KTH(a, b, c));
			}
		}
		printf("\n");
	}
} 
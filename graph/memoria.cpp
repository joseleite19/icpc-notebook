#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define pb push_back

const int oo = 1000000000;

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<pii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;

int p[50005], L[50005], vis[50005], n, root;
vvi g;

int dfs(int u){
	vis[u] = 1;
	for(int i = 0; i < g[u].size(); i++){
		if(vis[ g[u][i] ] == 0){
			p[ g[u][i] ] = u;
			L[ g[u][i] ] = L[u]+1;
			dfs(g[u][i]);
		}
	}
}

int dp[50005][20];

int f(int u, int level){
	if(dp[u][level] != -1) return dp[u][level];

	if(level == 0) return p[u];

	return dp[u][level] = f(f(u, level-1), level-1);
}

int lg(int n){
	int ans = 0;
	while(n)
		ans++, n/=2;
	return ans;
}

int LCA(int u, int v){
	if(L[u] < L[v]) swap(u, v);
	int k = lg(L[u]);
	
	for(int k = lg(L[u]); k >= 0; k--)
		if(L[ f(u, k) ] >= L[v])
			u = f(u, k);

	if(u == v) return u;

	for(int k = lg(L[u]); k >= 0; k--){
		if(f(u, k) != f(v, k)){
			u = f(u, k);
			v = f(v, k);
		}
	}

	return p[u];
}


int main(){
	int a, b;
	scanf("%d", &n);

	vvi c(n+1);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a);
		c[a].pb(i);
	}

	g.assign(n+1, vi());
	for(int i = 1; i < n; i++){
		scanf("%d %d", &a, &b);
		g[a].pb(b);
		g[b].pb(a);
	}

	memset(vis, 0, sizeof vis);
	root = 1;
	p[root] = root;
	L[root] = 0;
	dfs(root);

	memset(dp, -1, sizeof dp);

	int ans = 0;
	for(int i = 1; i <= n/2; i++)
		ans += L[ c[i][0] ] + L[ c[i][1] ] - 2*L[ LCA(c[i][0], c[i][1]) ];

	printf("%d\n", ans);
}
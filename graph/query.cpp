int p[N], L[N], vis[N], dp[N][MAXL], pw[N], dp2[N][MAXL]; 
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
		if(L[u] - (1 << i) >= L[v])
			u = f(u, i);

	if(u == v) return v;

	for(int i = MAXL-1; i >= 0; i--)
		if(L[u] - (1 << i) && f(u, i) != f(v, i))
			u = f(u, i), v = f(v, i);

	return p[u];
} 

long long DIST(int u, int v){
	if(L[u] < L[v]) swap(u, v);

	ll ans = 0;

	for(int i = MAXL-1; i >= 0; i--)
		if(L[u] - (1 << i) >= L[v])
			ans += h(u, i), u = f(u, i);

	if(u == v) return ans;

	for(int i = MAXL-1; i >= 0; i--)
		if(L[u] > (1 << i) && f(u, i) != f(v, i))
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
			if(L[v] - (1 << i) - L[lca] >= c)
				v = f(v, i);
		return v;
	}
	else{
		for(int i = MAXL-1; i >= 0; i--)
			if(L[a] - (L[u] - (1 << i)) + 1 <= c)
				u = f(u, i);
		return u;
 
	}
	return 0;
}

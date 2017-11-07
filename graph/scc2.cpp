
int num[N], low[N], vis[N], cor[N];
vector<int> g[N], S;

int t, e;
void dfs(int u){
	low[u] = num[u] = t++;
	S.push_back(u);
	vis[u] = 1;
	for(int v : g[u]){
		if(num[v] == -1) dfs(v);
		if(vis[v]) low[u] = min(low[u], low[v]);
	}
	if(low[u] == num[u]){
		e++;
		int v;
		do{
			v = s.back(), s.pop_back();
			vis[v] = 0, cor[v] = e;
		}while(v != u);
	}
}

int main(){
	memset(num, -1, sizeof num);
	memset(vis, 0, sizeof vis);
	memset(low, 0, sizeof low);
	for(int i = 1; i <= n; i++) if(num[i] == -1)
		dfs(i);
}

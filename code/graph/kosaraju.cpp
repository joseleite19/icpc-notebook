vector<int> g[N], gt[N], S;

int vis[N], cor[N], tempo = 1;

void dfs(int u){
	vis[u] = 1;
	for(int v : g[u]) if(!vis[v]) dfs(v);
	S.push_back(u);
}
int e;
void dfst(int u){
	cor[u] = e;
	for(int v : gt[u]) if(!cor[v]) dfst(v);
}

int main(){
	
	for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i);

	e = 0;
	reverse(S.begin(), S.end());
	for(int u : S) if(!cor[u])
		e++, dfst(u);

	return 0;
}

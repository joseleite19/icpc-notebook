int cnt = 0, root;
void dfs(int u, int p = -1){
	low[u] = num[u] = ++t;
	for(int v : g[u]){
		if(!num[v]){
			dfs(v, u);
           		if(u == root) cnt++;
			if(low[v] >= num[u]) u PONTO DE ARTICULACAO;
			if(low[v] > num[u]) ARESTA u->v PONTE;
			low[u] = min(low[u], low[v]);
		}
		else if(v != p) low[u] = min(low[u], num[v]);
	}
}

root PONTO DE ARTICULACAO <=> cnt > 1

void tarjanSCC(int u){
	low[u] = num[u] = ++cnt;
	vis[u] = 1;
	S.push_back(u);
	for(int v : g[u]){
		if(!num[v]) tarjanSCC(v);
		if(vis[v]) low[u] = min(low[u], low[v]);
	}
	if(low[u] == num[u]){
		ssc[u] = ++ssc_cnt; int v;
		do{
			v = S.back(); S.pop_back(); vis[v] = 0;
			ssc[v] = ssc_cnt;
		}while(u != v);
	}
}

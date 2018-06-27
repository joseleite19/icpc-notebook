void dfs(int u, int p = -1){
	low[u] = num[u] = ++t;
	for(int v : g[u]){
		if(!num[v]){
			dfs(v, u);
			if(low[v] >= num[u]) u PONTO DE ARTICULACAO;
			if(low[v] > num[u]){
				ARESTA u->v PONTE;
			}
			low[u] = min(low[u], low[v]);
		}
		else if(v != p) low[u] = min(low[u], num[v]);
	}
}


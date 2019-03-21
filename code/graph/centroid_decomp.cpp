vector<pair<int,int>> G[500005];
int subtree[500005], k;
bool erased[500005];
ll dist[500005], ans;

int calc_sz(int v, int p){
	subtree[v] = 1;
	for(auto x : G[v]) if(!erased[x.ff] && x.ff != p){
        subtree[v] += calc_sz(x.ff,v);
	return subtree[v];
}

int centroid(int v, int p, int treesize){
	for(auto x : G[v]) if(!erased[x.ff] && x.ff != p){
		if(subtree[x.ff] * 2 > treesize)
            return centroid(x.ff, v, treesize);
	}
	return v;
}

void procurar_ans(int v, int p, int d_atual, ll custo){
	ans = min(ans, dist[k - d_atual] + custo);
	if(d_atual == k) return;
	for(auto x : G[v]) if(!erased[x.ff] && x.ff != p)
        procurar_ans(x.ff, v, d_atual+1, custo+x.ss);
}

void atualiza_dist(int v, int p, int d_atual, ll custo){
	dist[d_atual] = min(dist[d_atual], custo);
	if(d_atual == k) return;
	for(auto x : G[v]) if(!erased[x.ff] && x.ff != p)
        atualiza_dist(x.ff,v,d_atual+1,custo+x.ss);
}

void decomp(int v, int p){
	int treesize = calc_sz(v, v);
	if(treesize < k) return;
	int cent = centroid(v, v, treesize);
	erased[cent] = 1;

	for(int i = 1; i <= treesize; i++) dist[i] = 1e18;

    for(pair<int,int> x : G[cent]) if(!erased[x.ff]){
        procurar_ans(x.ff, cent, 1, x.ss);
        atualiza_dist(x.ff, cent, 1, x.ss);
    }

	for(pair<int,int> x : G[cent]) if(!erased[x.ff])
        decomp(x.ff, cent);
}


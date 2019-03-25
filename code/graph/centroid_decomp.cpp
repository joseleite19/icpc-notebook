void decomp(int v, int p){
	int treesize = calc_sz(v, v);
	if(treesize < k) return;
	int cent = centroid(v, v, treesize);
	erased[cent] = 1;

	for(int i = 1; i <= treesize; i++) dist[i] = 1e18;

    for(pair<int,int> x : G[cent]) if(!erased[x.ff]){
        procurar_ans(x.ff, cent, 1, x.ss); // linear
        atualiza_dist(x.ff, cent, 1, x.ss); // linear
    }

	for(pair<int,int> x : G[cent]) if(!erased[x.ff])
        decomp(x.ff, cent);
}


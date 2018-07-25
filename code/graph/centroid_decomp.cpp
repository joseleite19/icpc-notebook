#include <bits/stdc++.h>

#define ff first
#define ss second
#define mp make_pair

using namespace std;

typedef long long ll;

vector<pair<int,int>> G[500005];
int subtree[500005], treesize, k;
bool vis[500005];
ll dist[500005], ans;

int dfs(int v, int p){
	subtree[v] = 1;
	for(pair<int,int> x : G[v])
		if(x.ff != p && !vis[x.ff]) subtree[v] += dfs(x.ff,v);
	return subtree[v];
}

int centroid(int v, int p){
	for(pair<int,int> x : G[v]){
		if(x.ff == p || vis[x.ff]) continue;
		if(subtree[x.ff]*2 > treesize) return centroid(x.ff,v);
	}
	return v;
}

void procurar_ans(int v, int p, int d_atual, ll custo){
	ans = min(ans, dist[k-d_atual] + custo);
	if(d_atual == k) return;
	for(pair<int,int> x : G[v]){
		if(!vis[x.ff] && x.ff != p)
			procurar_ans(x.ff,v,d_atual+1,custo+x.ss);
	}
}

void atualiza_distancia(int v, int p, int d_atual, ll custo){
	dist[d_atual] = min(dist[d_atual], custo);
	if(d_atual == k) return;
	for(pair<int,int> x : G[v]){
		if(!vis[x.ff] && x.ff != p)
			atualiza_distancia(x.ff,v,d_atual+1,custo+x.ss);
	}
}

void decomp(int v, int p){
	treesize = dfs(v,v);
	// if(treesize < k) return;
	int cent = centroid(v,v);
	vis[cent] = 1;

	for(int i = 1; i <= treesize; i++)
		dist[i] = 1e18;

	for(pair<int,int> x : G[cent]){
		if(!vis[x.ff]){
			procurar_ans(x.ff,cent,1,x.ss);
			atualiza_distancia(x.ff,cent,1,x.ss);
		}
	}

	for(pair<int,int> x : G[cent]){
		if(!vis[x.ff])
			decomp(x.ff, cent);
	}
}

int main(){
	int n,i,a,b;

	scanf("%d%d", &n,&k);
	for(i = 2; i <= n; i++){
		scanf("%d%d", &a,&b);
		G[i].push_back(mp(a,b));
		G[a].push_back(mp(i,b));
	}
	ans = 1e18;
	decomp(1,-1);

	printf("%lld\n", ans == 1e18 ? -1 : ans);

	return 0;
}

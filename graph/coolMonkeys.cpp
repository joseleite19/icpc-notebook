#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second
#define pb push_back
#define mp make_pair

const int oo = 1000000000;

typedef pair<int,int> ii;

vector<vector<int> > g;

int m, na, nb, t, source, target, ha[505], hb[505];
int mat[2020][2020], p[2020], vis[2020];

int back(int u, int minEdge){
	if(u == source) return minEdge;
	int f = back(p[u], min(minEdge, mat[ p[u] ][u]));
	mat[ p[u] ][u] -= f;
	mat[u][ p[u] ] += f;
	return f;
}

int maxflow(){
	int mf = 0, f = 1;
	while(f){
		queue<int> q;
		q.push(source);
		memset(vis, 0, sizeof vis);

		vis[source] = 1;
		p[source] = source;

		while(!q.empty()){
			int u = q.front(); q.pop();

			if(u == target) break;

			for(int i = 0; i < g[u].size(); i++){
				int v = g[u][i];
				if(mat[u][v] > 0 && vis[v] != 1){
					vis[v] = 1;
					p[v] = u;
					q.push(v);
				}
			}
		}

		if(vis[target] != 1) break;
		f = back(target, oo);
		mf += f;

	}
	return mf;
}

int buildRun(int *ha, int na, int *hb, int nb){
	g.assign(2020, vector<int>());
	sort(ha, ha+na, greater<int>());
	sort(hb, hb+nb);

	memset(mat, 0, sizeof mat);

	int cnt = 0;
	for(int i = 0; i < na; i++){
		for(int j = 0; j < nb; j++){
			int vin = i;
			int uin = na+j;
			int vout = na+nb+i;
			int uout = na+nb+na+j;
			if(abs(ha[i] - hb[j]) < t){
				// vout -> uin
				// uout -> vin
				// printf("%d -> %d\n", i, j);
				g[vout].pb(uin);
				g[uin].pb(vout);
				g[uout].pb(vin);
				g[vin].pb(uout);
				mat[vout][uin] = oo;
				mat[uout][vin] = oo;
			}
		}
	}

	for(int i = 0; i < na; i++){
		int vin = i;
		int vout = na+nb+i;
		g[vin].pb(vout);
		g[vout].pb(vin);
		mat[vin][vout] = 1;
	}


	for(int j = 0; j < nb; j++){
		int uin = na+j;
		int uout = na+nb+na+j;
		g[uin].pb(uout);
		g[uout].pb(uin);
		mat[uin][uout] = 1;
	}

	for(int i = 0; i < m; i++){
		int vin = i;
		int uout = na+nb+na+i;
		g[source].pb(vin);
		g[vin].pb(source);
		mat[source][vin] = 1;

		g[uout].pb(target);
		g[target].pb(uout);
		mat[uout][target] = 1;
	}

	return maxflow();
}

int main(){
	source = 2018;
	target = 2019;

	scanf("%d %d %d %d", &m, &na, &nb, &t);

	for(int i = 0; i < na; i++)
		scanf("%d", ha+i);
	for(int i = 0; i < nb; i++)
		scanf("%d", hb+i);

	if(buildRun(ha, na, hb, nb)  == m || buildRun(hb, nb, ha, na) == m) printf("S\n");
	else printf("N\n");

	return 0;
}
#include <bits/stdc++.h>

#define mp make_pair
#define ff first
#define ss second

using namespace std;

typedef long long ll;

vector<pair<int,int>> G[100005];
int lvl[100005], p[100005], anc[100005][20], logg;
ll dist[100005];

void dfs(int v, int l, ll d){
    lvl[v] = l;
    dist[v] = d;
    for(pair<int,int> &x : G[v]){
        if(lvl[x.ff] == -1){
            p[x.ff] = v;
            dfs(x.ff, l+1,d+x.ss);
        }
    }
}

int LCA(int u, int v){
    if(lvl[u] < lvl[v]) swap(u,v);

    for(int i = logg; i >= 0; i--)
        if(lvl[u] - (1<<i) >= lvl[v])
            u = anc[u][i];

    if(u == v) return u;
    
    for(int i = logg; i >= 0; i--){
        if(anc[u][i] != -1 && anc[u][i] != anc[v][i]){
            u = anc[u][i];
            v = anc[v][i];
        }
    }

    return anc[u][0];
}

int main() {
    int a,b,n,q,i,j;
    
	while(scanf("%d", &n),n){
		for(int i = 1; i <= n-1; i++){
			scanf("%d%d", &a,&b);
			G[i].push_back(mp(a,b));
			G[a].push_back(mp(i,b));
			lvl[i] = -1;
		}
		dfs(0,0,0);
		for(logg = 0; 1<<logg <= n; logg++);
		for(i = 0; i < n; i++)
        		for(j = 0; j < logg; j++)
        		    anc[i][j] = -1;
		for(i = 0; i < n; i++)
        		anc[i][0] = p[i];
    		for(j = 1; j <= logg; j++)
        		for(i = 0; i < n; i++)
             			if(anc[i][j-1] != -1)
                 			anc[i][j] = anc[ anc[i][j-1] ][j-1];
		scanf("%d", &q);
		while(q--){
			scanf("%d%d", &a,&b);
			int x = LCA(a,b);
			ll ans = dist[a]+dist[b]-2*dist[x];
			if(q) printf("%lld ", ans);
			else printf("%lld", ans);
		}
		printf("\n");
		for(i = 0; i < n; i++) G[i].clear();
	}
 
    return 0;
}

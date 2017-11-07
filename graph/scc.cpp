#include <bits/stdc++.h>

using namespace std;

const int N = 100005;

vector<int> g[N], gt[N];

int tempo = 1;
int c[N], f[N], cor[N];

void dfs(int u){
	c[u] = tempo++;

	for(int v : g[u]) if(!c[v])
		dfs(v);

	f[u] = tempo++;
}

void dfst(int u, int c){
	cor[u] = c;
	for(int v : gt[u]) if(!cor[v])
		dfst(v, c);
}

int main(){

	int n, m;

	scanf("%d %d", &n, &m);
	
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		gt[v].push_back(u);
	}
	memset(c, 0, sizeof c);
	memset(f, 0, sizeof f);
	memset(cor, 0, sizeof color);

	for(int i = 1; i <= n; i++) if(!c[i])
		dfs(i);

	vector<int> tmp;
	for(int i = 1; i <= n; i++)
		tmp.push_back(i);
	
	sort(tmp.begin(), tmp.end(), [=](int a, int b){
		return f[a] > f[b];
	});

	int e = 0;
	for(int u : tmp) if(!cor[u])
		dfst(u, ++e);

	return 0;
}

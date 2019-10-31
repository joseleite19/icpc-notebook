// O(V * E)
int match[N];
int vis[N], pass;
vector<int> g[N];

bool dfs(int u) {
	vis[u] = pass;

	for(int v : g[u]) if(vis[v] != pass) {
		vis[v] = pass;
		if(match[v] == -1 or dfs(match[v])) {
			match[v] = u;
			match[u] = v;
			return true;
		}
	}
	return false;
}

int max_maching() {
	memset(match, -1, sizeof match);
	int max_matching_size = 0;
	for(int u : vertices_on_side_A) {
		pass++;
		if(dfs(i)) max_matching_size++;
	}
	return max_matching_size;
}

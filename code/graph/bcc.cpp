vector<int> S;
void create_comp(int id) {
	nxt_id++;
	int eid;
	do {
		eid = S.back();
		S.pop_back();
		comp_id[eid] = nxt_id;
	} while(!S.empty() and eid != id);
}
void dfs(int u, int pid){
	low[u] = num[u] = ++dfst;
	int cnt = 0;
	bool is_root = pid == -1;
	for(auto [v, eid] : g[u]) if(eid != pid) {
		if(!used[eid]) {
			used[eid] = true;
			S.push_back(eid);
		}
		if(!num[v]) {
			dfs(v, eid);
			cnt++;
			if(is_root ? cnt > 1 : low[v] >= num[u]) {
				art[u] = 1;
				create_comp(eid);
			}
			if(low[v] >= num[u]) { /* bridge */ }
			low[u] = min(low[u], low[v]);
		}
		else low[u] = min(low[u], num[v]);
	}
	if(is_root and !S.empty()) {
		create_comp(-1);
	}
}

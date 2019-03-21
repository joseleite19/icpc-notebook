struct DSU{
	vector<int> sz, p, change;
	vector<tuple<int, int, int>> modifications;
	vector<size_t> saves;
	bool bipartite;

	DSU(int n): sz(n+1, 1), p(n+1), change(n+1), bipartite(true){
		iota(p.begin(), p.end(), 0);
	}

	void add_edge(int u, int v){
		if(!bipartite) return;
		int must_change = get_colour(u) == get_colour(v);
		int a = rep(u), b = rep(v);
		if(sz[a] < sz[b]) swap(a, b);
		if(a != b){
			p[b] = a;
			modifications.emplace_back(b, change[b], bipartite);
			change[b] ^= must_change;
			sz[a] += sz[b];
		}
		else if(must_change){
			modifications.emplace_back(0, change[0], bipartite);
			bipartite = false;
		}
	}

	int rep(int u){
		return p[u] == u ? u : rep(p[u]);
	}

	int get_colour(int u){
		if(p[u] == u) return change[u];
		return change[u] ^ get_colour(p[u]);
	}

	void reset(){
		modifications.clear();
		saves.clear();
		iota(p.begin(), p.end(), 0);
		fill(sz.begin(), sz.end(), 1);
		fill(change.begin(), change.end(), 0);
		bipartite = true;
	}

	void rollback(){
		int u = get<0>(modifications.back());
		tie(ignore, change[u], bipartite) = modifications.back();
		sz[ p[u] ] -= sz[u];
		p[u] = u;
		modifications.pop_back();
	}

	void reload(){
		while(modifications.size() > saves.back())
			rollback();
		saves.pop_back();
	}

	void save(){
		saves.push_back(modifications.size());
	}
};

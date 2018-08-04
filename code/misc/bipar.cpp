#include <bits/stdc++.h>

using namespace std;

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

const int N = 100005;
const int B = 318;

int n, m, q;
int x[N], y[N], l[N], r[N], ans[N];

vector<int> qu[N];

int brute(int lef, int rig, DSU &s){
	s.save();
	for(int i = lef; i <= rig; i++)
		s.add_edge(x[i], y[i]);
	int ret = s.bipartite;
	s.reload();
	return ret;
}

int main(){

	scanf("%d %d %d", &n, &m, &q);

	for(int i = 1; i <= m; i++)
		scanf("%d %d", x+i, y+i);

	DSU s(n);
	for(int i = 0; i < q; i++){
		scanf("%d %d", l+i, r+i);
		if(r[i] - l[i] <= B + 10)
			ans[i] = brute(l[i], r[i], s);
		else qu[l[i] / B].push_back(i);
	}

	for(int i = 0; i <= m / B; i++){
		sort(qu[i].begin(), qu[i].end(),[](int a, int b){
			return r[a] < r[b];
		});
		s.reset();

		int R = (i+1)*B-1;

		for(int id : qu[i]){
			while(R < r[id]) ++R, s.add_edge(x[R], y[R]);
			s.save();
			for(int k = l[id]; k < (i+1)*B; k++)
				s.add_edge(x[k], y[k]);
			ans[id] = s.bipartite;
			s.reload();
		}
	}

	for(int i = 0; i < q; i++)
		printf("%s\n",ans[i] ? "Possible":"Impossible");
}

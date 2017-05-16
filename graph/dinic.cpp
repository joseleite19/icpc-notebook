#include <bits/stdc++.h>

#define ff first
#define ss second
#define mp make_pair
#define oo 1000000000

using namespace std;

vector<pair<int, pair<long long, int> > > g[100005]; // <vx, <edge weight, id reverse edge>>

int lvl[100005], vis[100005], source, target;

size_t px[100005];

long long run(int s, long long minE){
	if(s == target) return minE;

	long long ans = 0;

	for(; px[s] < g[s].size(); px[s]++){
		auto &v = g[s][ px[s] ];
		if(lvl[v.ff] != lvl[s]+1 || !v.ss.ff) continue;
		long long tmp = run(v.ff, min(minE, v.ss.ff));
		v.ss.ff -= tmp;
		g[v.ff][v.ss.ss].ss.ff += tmp;
		ans += tmp;
		minE -= tmp;
		if(minE == 0) break;
	}
	return ans;
}

int pass;
int bfs(){

	queue<int> q;
	q.push(source);
	lvl[source] = 1;
	vis[source] = ++pass;

	while(!q.empty()){
		int u = q.front(); q.pop();
		px[u] = 0;

		for(auto v : g[u]){
			if(v.ss.ff <= 0 || vis[v.ff] == pass) continue;
			vis[v.ff] = pass;
			lvl[v.ff] = lvl[u]+1;
			q.push(v.ff);
		}
	}

	return vis[target] == pass;
}

long long flow(){

	long long ans = 0;
	while(bfs())
		ans += run(source, oo);
	return ans;
}

void addEdge(int u, int v, long long c){
	pair<int, pair<long long, int> > a, b;
	a = {u, {0, g[u].size()}};
	b = {v, {c, g[v].size()}};
	g[u].push_back(b);
	g[v].push_back(a);
}

int ptr = 1;

class Segtree{
	vector<int> st;
	vector<int> id;
	int final;
	int n;

	vector<int> ans;

	void get(int p, int L, int R, int i, int j){
		if(j < L || i > R) return;
		if(i <= L && R <= j){ // CONSIDERA
			ans.push_back(id[p]);
			return;
		}
		int mid = (L+R)/2;
		get(2*p, L, mid, i, j);
		get(2*p+1, mid+1, R, i, j);
	}

	void init(int p, int L, int R){
		id[p] = ptr++;
		if(L == R){
			if(final == source) addEdge(final, id[p], 1);
			else if(final == target) addEdge(id[p], final, 1);
			return;
		}
		int mid = (L+R)/2;
		init(2*p, L, mid);
		init(2*p+1, mid+1, R);

		if(final == source) addEdge(id[2*p], id[p], oo), addEdge(id[2*p+1], id[p], oo);
		else if(final == target) addEdge(id[p], id[2*p], oo), addEdge(id[p], id[2*p+1], oo);
	}

public:
	Segtree(int size, int final) : n(size), st(4*(size+5), 0), id(4*(size+5), 0), final(final){
		init(1, 1, n);
	}

	vector<int> get(int i, int j){
		ans.clear();
		get(1, 1, n, i, j);
		return ans;
	}
};

vector<pair<int, pair<int, pair<int, int> > > > p;

int main(){
	int n, q;

	scanf("%d %d", &n, &q);

	for(int i = 0; i < q; i++){
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		p.push_back(mp(x1, mp(1, mp(y1, y2))));
		p.push_back(mp(x2+1, mp(-1, mp(y1, y2))));
	}
	p.push_back(mp(1, mp(-1, mp(1, n))));
	p.push_back(mp(n+1, mp(1, mp(0, n+1))));

	sort(p.begin(), p.end());

	target = ptr++;

	Segtree stl(n, source); // x
	Segtree str(n, target); // y

	set<pair<int, pair<int, int > > > s; // <y1, <y2, x> >

	for(int i = 0; i < p.size(); i++){
		if(p[i].ss.ff == 1){ //new rectangle, build edges beetween intercession
			while(1){
				if(s.empty()) break;
				auto it = s.upper_bound(mp(p[i].ss.ss.ff, mp(oo, oo)));
				if(it != s.begin()){
					it--;
					if(it->ff > p[i].ss.ss.ss || it->ss.ff < p[i].ss.ss.ff) it++;
				}
				if(it == s.end()) break;
				if(it->ff > p[i].ss.ss.ss || it->ss.ff < p[i].ss.ss.ff) break;

				vector<int> vl = stl.get(it->ss.ss, p[i].ff-1);
				vector<int> vr = str.get(max(it->ff, p[i].ss.ss.ff), min(it->ss.ff, p[i].ss.ss.ss));

				for(int u : vl) for(int v : vr)
					addEdge(u, v, oo);
				if(it->ff < p[i].ss.ss.ff) s.insert(mp(it->ff, mp(p[i].ss.ss.ff-1, it->ss.ss)));
				if(it->ss.ff > p[i].ss.ss.ss) s.insert(mp(p[i].ss.ss.ss+1, mp(it->ss.ff, it->ss.ss)));

				s.erase(it);
			}
		}
		else s.insert(mp(p[i].ss.ss.ff, mp(p[i].ss.ss.ss, p[i].ff)));
	}

	printf("%lld\n", flow());

	return 0;
}
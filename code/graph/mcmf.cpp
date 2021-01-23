const ll oo = 1e18;
const int N = 422, E = 2 * 10006;
 
vector<int> g[N];
int ne;
struct Edge{
    int from, to; ll cap, cost;
} edge[E];
int start = N-1, target = N-2, p[N]; int inqueue[N];
ll d[N];
ll pot[N];
bool dijkstra(int source, int sink) {
	for(int i = 0; i < N; i++) d[i] = oo;
	d[source] = 0;
	priority_queue<pair<ll, int>> q;
	q.emplace(0, source);
	ll dt; int u;
	while(!q.empty()) {
		tie(dt, u) = q.top(); q.pop(); dt = -dt;
		if(dt > d[u]) continue;
		if(u == sink) return true;
		for(int e : g[u]) {
			auto v = edge[e];
			const ll cand = d[u] + v.cost + pot[u] - pot[v.to];
			if(v.cap > 0 and cand < d[v.to]) {
				p[v.to] = e;
				d[v.to] = cand;
				q.emplace(-d[v.to], v.to);
			}
		}
	}
	return d[sink] < oo;
}
 
// <max flow, min cost>
pair<ll, ll> mincost(int source = start, int sink = target){
    ll ans = 0, mf = 0;
    while(dijkstra(source, sink)){
        ll f = oo;
        for(int u = sink; u != source; u = edge[ p[u] ].from)
            f = min(f, edge[ p[u] ].cap);
        mf += f;
        ans += f * (d[sink] - pot[source] + pot[sink]);
        for(int u = sink; u != source; u = edge[ p[u] ].from){
            edge[ p[u] ].cap -= f;
            edge[ p[u] ^ 1 ].cap += f;
        }
		for(int i = 0; i < N; i++) pot[i] = min(oo, pot[i] + d[i]);
    }
    return {mf, ans};
}
void addEdge(int u, int v, ll c, ll cost){
	assert(cost >= 0); //IF not, pot[i]=short.path source
    edge[ne] = {u, v, c, cost};
    g[u].push_back(ne++);
    edge[ne] = {v, u, 0,-cost};
    g[v].push_back(ne++);
}


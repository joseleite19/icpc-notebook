const ll oo = 1e18;
const int N = 222, E = 2 * 1000006;

vector<int> g[N];
int ne;
struct Edge{
    int from, to; ll cap, cost;
} edge[E];
int start = N-1, target = N-2, p[N]; int inqueue[N];
ll d[N];
bool spfa(int source, int sink){
    for(int i = 0; i < N; i++) d[i] = oo;
    inqueue[i] = 0;

    d[source] = 0; queue<int> q; q.push(source);
    inqueue[source] = 1;

    while(!q.empty()){
        int u = q.front(); q.pop();
        inqueue[u] = 0;
        for(int e : g[u]){
            auto v = edge[e];
            if(v.cap > 0 and d[u] + v.cost < d[v.to]){
                d[v.to] = d[u] + v.cost; p[v.to] = e;
                if(!inqueue[v.to]){
                    q.push(v.to); inqueue[v.to] = 1;
                }
            }
        }
    }
    return d[sink] != oo;
}
// <max flow, min cost>
pair<ll, ll> mincost(int source = start, int sink = target){
    ll ans = 0, mf = 0;
    while(spfa(source, sink)){
        ll f = oo;
        for(int u = sink; u != source; u = edge[ p[u] ].from)
            f = min(f, edge[ p[u] ].cap);
        for(int u = sink; u != source; u = edge[ p[u] ].from){
            edge[ p[u] ].cap -= f;
            edge[ p[u] ^ 1 ].cap += f;
        }
        mf += f;
        ans += f * d[sink];
    }
    return {mf, ans};
}
void addEdge(int u, int v, ll c, ll cost){
    edge[ne] = {u, v, c, cost};
    g[u].push_back(ne++);
    edge[ne] = {v, u, 0,-cost};
    g[v].push_back(ne++);
}

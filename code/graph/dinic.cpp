const int N = 100005;
const int E = 2000006;
vector<int> g[N];

int ne;
struct Edge{
    int from, to;
    ll flow, cap;
} edge[E];

int lvl[N], vis[N], pass, start = N-2, target = N-1;
int qu[N], qt, px[N];

ll run(int s, int sink, ll minE){
    if(s == sink) return minE;

    ll ans = 0;

    for(; px[s] < (int)g[s].size(); px[s]++){
        int e = g[s][ px[s] ];
        auto &v = edge[e], &rev = edge[e^1];
        if(lvl[v.to] != lvl[s]+1 || v.flow >= v.cap)
            continue;           // v.cap - v.flow < lim
        ll tmp = run(v.to, sink,min(minE, v.cap-v.flow));
        v.flow += tmp, rev.flow -= tmp;
        ans += tmp, minE -= tmp;
        if(minE == 0) break;
    }
    return ans;
}

bool bfs(int source, int sink){
    qt = 0;
    qu[qt++] = source;
    lvl[source] = 1;
    vis[source] = ++pass;

    for(int i = 0; i < qt; i++){
        int u = qu[i];
        px[u] = 0;
		if(u == sink) return true;

        for(int e : g[u]){
            auto v = edge[e];
            if(v.flow >= v.cap || vis[v.to] == pass)
                continue; // v.cap - v.flow < lim
            vis[v.to] = pass;
            lvl[v.to] = lvl[u]+1;
            qu[qt++] = v.to;
        }
    }
    return false;
}

ll flow(int source = start, int sink = target){
    ll ans = 0;
    //for(lim = (1LL << 62); lim >= 1; lim /= 2)
    while(bfs(source, sink))
		ans += run(source, sink, oo);
    return ans;
}

void addEdge(int u, int v, ll c = 1, ll rc = 0){
    edge[ne] = {u, v, 0, c};
    g[u].push_back(ne++);
    edge[ne] = {v, u, 0, rc};
    g[v].push_back(ne++);
}

void reset_flow(){
	for(int i = 0; i < ne; i++)
		edge[i].flow = 0;
}


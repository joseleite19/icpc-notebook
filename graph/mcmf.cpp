#include <bits/stdc++.h>

#define forn(i, n) for(int i = 0; i < int(n); i++)
#define fore(i, a, b) for(int i = int(a); i <= int(b); i++)
#define ff first
#define ss second
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define eb emplace_back

using namespace std;

typedef long long ll;
const ll oo = 1e18;
const int N = 505;
const int E = 30006;

vector<int> g[N];

int ne;

struct Edge{
    int from, to;
    ll cap, cost;
} edge[E];

int lvl[N], vis[N], pass, source, target, p[N], px[N];

ll d[N];

ll back(int s, ll minE){
    if(s == source) return minE;

    int e = p[s];

    ll f = back(edge[e].from, min(minE, edge[e].cap));
    edge[e].cap -= f;
    edge[e^1].cap += f;
    return f;
}

int dijkstra(){
    forn(i, N) d[i] = oo;

    priority_queue<pair<ll, int> > q;

    d[source] = 0;

    q.emplace(0, source);

    while(!q.empty()){
        ll dis = -q.top().ff;
        int u = q.top().ss; q.pop();

        if(dis > d[u]) continue;

        for(int e : g[u]){
            auto v = edge[e];
            if(v.cap <= 0) continue;
            if(d[u] + v.cost < d[v.to]){
                d[v.to] = d[u] + v.cost;
                p[v.to] = e;
                q.emplace(-d[v.to], v.to);
            }
        }
    }
    return d[target] != oo;
}

pair<ll, ll> mincost(){
    ll ans = 0, mf = 0;
    while(dijkstra()){
        ll f = back(target, oo);
        mf += f;
        ans += f * d[target];
    }
    return {mf, ans};
}

void addEdge(int u, int v, ll c, ll cost){
    edge[ne] = {u, v, c, cost};
    g[u].pb(ne++);
}

char s[55][55];

int main(){

    int n, m;
    for(int tc = 1; scanf("%d %d", &n, &m) == 2; tc++){
        ne = 0;

        int a, b, c;
        forn(i, m){
            scanf("%d %d %d", &a, &b, &c);
            addEdge(a, b, 0, c);
            addEdge(b, a, 0, -c);
            addEdge(b, a, 0, c);
            addEdge(a, b, 0, -c);
        }
        int d, k;

        scanf("%d %d", &d, &k);

        forn(i, ne) if(i % 2 == 0) edge[i].cap = k;

        source = 0, target = n;

        addEdge(0, 1, d, 0);
        addEdge(1, 0, 0, 0);

        pair<ll, ll> ans = mincost();
        printf("Instancia %d\n", tc);
        if(ans.ff < d) printf("impossivel\n");
        else printf("%lld\n", ans.ss);

        printf("\n");
        forn(i, N) g[i].clear();
    }

}


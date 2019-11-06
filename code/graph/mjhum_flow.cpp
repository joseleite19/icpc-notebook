#include <bits/stdc++.h>
#ifdef DEMETRIO
#define deb(...) fprintf(stderr,__VA_ARGS__)
#define deb1(x) cerr << #x << " = " << x << endl
#else
#define deb(...) 0
#define deb1(x) 0
#endif
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define SZ(x) ((int)(x).size())
#define mset(a,v) memset(a,v,sizeof(a))
#define mcpy(a,b) memcpy(a,b,sizeof(a))
using namespace std;
typedef long long ll;

#define MAXN 100055

int nodes,src,dst;
int dist[MAXN],q[MAXN],work[MAXN];
struct edge {int to,rev;ll f,cap;};
vector<edge> g[MAXN];
void add_edge(int s, int t, ll cap){
	g[s].pb((edge){t,SZ(g[t]),0,cap});
	g[t].pb((edge){s,SZ(g[s])-1,0,0});
}
bool dinic_bfs(){
	fill(dist,dist+nodes,-1);dist[src]=0;
	int qt=0;q[qt++]=src;
	for(int qh=0;qh<qt;qh++){
		int u=q[qh];
		fore(i,0,SZ(g[u])){
			edge& e=g[u][i];int v=g[u][i].to;
			if(dist[v]<0&&e.f<e.cap)dist[v]=dist[u]+1,q[qt++]=v;
		}
	}
	return dist[dst]>=0;
}
ll dinic_dfs(int u, ll f){
	if(u==dst)return f;
	for(int& i=work[u];i<SZ(g[u]);i++){
		edge& e=g[u][i];
		if(e.cap<=e.f)continue;
		int v=e.to;
		if(dist[v]==dist[u]+1){
			ll df=dinic_dfs(v,min(f,e.cap-e.f));
			if(df>0){e.f+=df;g[v][e.rev].f-=df;return df;}
		}
	}
	return 0;
}
ll max_flow(int _src, int _dst){
	src=_src;dst=_dst;
	ll result=0;
	while(dinic_bfs()){
		fill(work,work+nodes,0);
		while(ll d=dinic_dfs(src,1LL<<60))result+=d;
	}
	return result;
}

int n,m,s;ll all;
map<int,ll> pingo;
vector<pair<int,ll> > ss;
ll p[100005];
ll d[11][100005];

vector<ll> qwe;

bool can(ll t){
	fore(i,0,nodes)g[i].clear();
	fore(i,0,s)add_edge(0,2+i,ss[i].snd);
	fore(i,0,n)add_edge(2+s+i,1,p[i]);
	fore(i,0,s)fore(j,0,n)if(d[i][j]<=t){
		//printf(" %lld %d %d\n",t,ss[i].fst+1,j+1);
		add_edge(2+i,2+s+j,1LL<<60);
	}
	ll asd=max_flow(0,1);
	//printf(" %lld %lld %lld\n",t,asd,all);
	return asd==all;
}

vector<pair<int,ll> > gg[100005];
priority_queue<pair<ll,int> > qq;

void dijkstra(int x, ll* d){
	fore(i,0,n)d[i]=-1;
	d[x]=0;
	qq.push(mp(0,x));
	while(!qq.empty()){
		int x=qq.top().snd;ll asd=-qq.top().fst;qq.pop();
		if(d[x]!=asd)continue;
		for(auto p:gg[x]){
			int y=p.fst;ll c=p.snd;
			if(d[y]<0||d[x]+c<d[y]){
				d[y]=d[x]+c;
				qq.push(mp(-d[y],y));
			}
		}
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&s);
	fore(i,0,n)scanf("%lld",p+i),all+=p[i];
	while(m--){
		int x,y;ll c;
		scanf("%d%d%lld",&x,&y,&c);x--;y--;
		gg[x].pb(mp(y,c));
		gg[y].pb(mp(x,c));
	}
	fore(_,0,s){
		int x;ll c;
		scanf("%d%lld",&x,&c);x--;
		pingo[x]+=c;
	}
	ss=vector<pair<int,ll> >(pingo.begin(),pingo.end());
	s=SZ(ss);
	fore(i,0,s)dijkstra(ss[i].fst,d[i]);
	nodes=2+s+n;
	fore(i,0,s)fore(j,0,n)qwe.pb(d[i][j]);
	sort(qwe.begin(),qwe.end());
	qwe.erase(unique(qwe.begin(),qwe.end()),qwe.end());
	fore(i,0,s)g[2+i].reserve(n);
	int s=0,e=SZ(qwe);
	while(e-s>1){
		int m=(s+e)/2;
		if(can(qwe[m-1]))e=m;
		else s=m;
	}
	printf("%lld\n",qwe[s]);
	return 0;
}

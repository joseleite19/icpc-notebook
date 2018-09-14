#include <bits/stdc++.h>

using namespace std;

const int N = 500005;
char s[N];
int n;

	map<char, int> t[N];
	int len[N], suf[N], vis[N];
class SuffixAutomaton{
	int last, ptr;
	int pass;

	void print(int u){
		vis[u] = pass;
		for(auto x : t[u]){
			printf("%d %d %c\n", u, x.second, x.first);
			if(vis[x.second] != pass) print(x.second);
		}
	}

	int cnt(int u){
		vis[u] = pass;
		int ans = 0;
		for(auto x : t[u]){
			ans++;
			if(vis[x.second] != pass) ans += cnt(x.second);
		}
		return ans;
	}
	void goup(int u){
		printf("%d ", u);
		if(suf[u]) goup(suf[u]);
	}
	int cnttt(int u){
		if(!u) return 0;
		return 1 + cnttt(suf[u]);
	}

public:
	SuffixAutomaton() : last(1), ptr(1), pass(0){}
	void add(char c){
		int p = last;
		int v = ++ptr;
		last = v;
		len[v] = len[p]+1;
		while(p && !t[p].count(c)){
			t[p][c] = v;
			p = suf[p];
		}
		if(!p){
			suf[v] = 1;
			return;
		}
		int u = t[p][c];
		if(len[p]+1 == len[u]){
			suf[v] = u;
			return;
		}
		int uu = ++ptr;
		t[uu] = t[u], suf[uu] = suf[u];
		len[uu] = len[p]+1;
		suf[v] = uu;
		suf[u] = uu;
		while(t[p].count(c) && t[p][c] == u){
			t[p][c] = uu;
			p = suf[p];
		}
	}
	int sz(){ return ptr; }
	int edges(){ return pass++, cnt(1); }
	void print(){ pass++, print(1); }
	void terminal(){
		goup(last); printf("\n");
	}
	int cntt(){
		return cnttt(last);
	}
};


int main(){

	scanf("%s", s), n = strlen(s);

	SuffixAutomaton sa;

	for(int i = 0; i < n; i++) sa.add(s[i]);

	printf("%d %d\n", sa.sz(), sa.edges());
	sa.print();
	printf("%d\n", sa.cntt());
	sa.terminal();

	return 0;
}

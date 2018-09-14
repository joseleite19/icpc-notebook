// source: https://github.com/victorsenam/caderno/blob/master/code/treap.cpp
//const int N = ; typedef int num;
num X[N]; int en = 1, Y[N], sz[N], L[N], R[N];
void calc (int u) { // update node given children info
	sz[u] = sz[L[u]] + 1 + sz[R[u]];
	// code here, no recursion
}
void unlaze (int u) {
	if(!u) return;
	// code here, no recursion
}
void split_val(int u, num x, int &l, int &r) { // l gets <= x, r gets > x
	unlaze(u); if(!u) return (void) (l = r = 0);
	if(X[u] <= x) { split_val(R[u], x, l, r); R[u] = l; l = u; }
	else { split_val(L[u], x, l, r); L[u] = r; r = u; }
	calc(u);
}
void split_sz(int u, int s, int &l, int &r) { // l gets first s, r gets remaining
	unlaze(u); if(!u) return (void) (l = r = 0);
	if(sz[L[u]] < s) { split_sz(R[u], s - sz[L[u]] - 1, l, r); R[u] = l; l = u; }
	else { split_sz(L[u], s, l, r); L[u] = r; r = u; }
	calc(u);
}
int merge(int l, int r) { // els on l <= els on r
	unlaze(l); unlaze(r); if(!l || !r) return l + r; int u;
	if(Y[l] > Y[r]) { R[l] = merge(R[l], r); u = l; }
	else { L[r] = merge(l, L[r]); u = r; }
	calc(u); return u;
}
void init(int n=N-1) { // XXX call before using other funcs
	for(int i = en = 1; i <= n; i++) { Y[i] = i; sz[i] = 1; L[i] = R[i] = 0; }
	random_shuffle(Y + 1, Y + n + 1);
}

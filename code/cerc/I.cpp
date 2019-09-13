CERC 17 I
class SegTree{
	vector<ii> st;
	void upd(int p, int nodeL, int nodeR, int queryL, int queryR, ii v){
		if(queryL <= nodeL and queryR >= nodeR){
			st[p] = v;
			return;
		}
		st[p] = {max(st[2*p].ff, st[2*p+1].ff), min(st[2*p].ss, st[2*p+1].ss)};
	}
};
int a[N], pos[N], prox[N];
ii ans[N];
void f(vector<pair<ii, int>> &qrys, int mid, int lo, int hi){
	int l = mid, r = mid+1;
	int id = 0;
	if(a[l] > a[r])
		id = l;
	else
		id = r;
	st.upd(id, id, id);
	vector<ii> lef;
	while(l >= lo){
		if(a[l] > a[id]){
			st.upd(id, id, prox[id]);
			id = l;
			st.upd(id, id, id);
		}
		ii ret = st.qry(l, r);
		if(ret.ff <= r && ret.ss >= l){
			lef.pb({l, r});
			l--;
		}
		else{
			while(ret.ss >= l && ret.ff <= hi){
				while(r < ret.ff){
					r++;
					if(a[r] > a[id]){
						st.upd(id, id, prox[id]);
						id = r;
						st.upd(id, id, id);
					}
				}
				ret = st.qry(l, r);
				if(ret.ff <= r && ret.ss >= l){
					lef.pb({l, r});
					break;
				}
				else if(ret.ff > hi || ret.ss < lo){
					l = lo - 1;
					break;
				}
				else if(ret.ss < l){
					break;
				}
			}
			l--;
		}
	}
	st.upd(id, id, prox[id]);
 
	l = mid, r = mid+1;
	if(a[l] > a[r])
		id = l;
	else
		id = r;
	st.upd(id, id, id);
	vector<ii> rig;
	while(r <= hi){
		if(a[r] > a[id]){
			st.upd(id, id, prox[id]);
			id = r;
			st.upd(id, id, id);
		}
		ii ret = st.qry(l, r);
		if(ret.ff <= r && ret.ss >= l){
			rig.pb({r, l});
			r++;
		}
		else{
			while(ret.ss >= lo && ret.ff <= r){
				while(l > ret.ss){
					l--;
					if(a[l] > a[id]){
						st.upd(id, id, prox[id]);
						id = l;
						st.upd(id, id, id);
					}
				}
				ret = st.qry(l, r);
				if(ret.ff <= r && ret.ss >= l){
					rig.pb({r, l});
					break;
				}
				else if(ret.ff > hi || ret.ss < lo){
					break;
				}
				else if(ret.ff > r){
					break;
				}
			}
			r++;
		}
	}
	st.upd(id, id, prox[id]);
 
	reverse(lef.begin(), lef.end());
	for(auto i : qrys){
		auto it1 = upper_bound(lef.begin(), lef.end(), make_pair(i.ff.ff, N));
		if(it1 == lef.begin()) continue;
		it1--;
		auto it2 = lower_bound(rig.begin(), rig.end(), make_pair(i.ff.ss, 0));
		if(it2 == rig.end()) continue;
		int le = min(it1->ff, it2->ss), re = max(it2->ff, it1->ss);
		if(re - le < ans[i.ss].ss - ans[i.ss].ff)
			ans[i.ss] = {le, re};
	}
 
}
 
void solve(vector<pair<ii, int>> &qrys, int lo, int hi){
	if(lo == hi) return;
 
	int mid = (lo + hi) / 2;
	if(mid+1 > hi) return;
	f(qrys, mid, lo, hi);
	vector<pair<ii, int>> lef, rig;
	for(auto i : qrys){
		if(i.ff.ss <= mid)
			lef.pb(i);
		if(i.ff.ff > mid)
			rig.pb(i);
	}
	solve(lef, lo, mid);
	solve(rig, mid+1, hi);
}
 
int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", a+i);
		pos[a[i]] = i;
	}
	st = SegTree(n+2);
	for(int i = 1; i <= n; i++){
		prox[i] = pos[a[i] + 1];
		st.upd(i, i, prox[i]);
	}
	int q;
	vector<pair<ii, int>> qrys;
	scanf("%d", &q);
	for(int i = 0; i < q; i++){
		ans[i] = {1, n};
		int l, r;
		scanf("%d %d", &l, &r);
		if(l == r){
			ans[i] = {l, r};
		}
		else{
			qrys.pb({{l, r}, i});
		}
	}
	solve(qrys, 1, n);
	for(int i = 0; i < q; i++){
		printf("%d %d\n", ans[i].ff, ans[i].ss);
	}
	return 0;
}
const int oo = 1e9+7;

struct SegBeats {
	int n;
	struct node {
		ll sum;
		int mx, smx, cnt;
	};
	node comb(const node &a, const node &b) {
		node ans{a.sum + b.sum, max(a.mx, b.mx),
				 max(a.smx, b.smx), 0};
		if(a.mx == ans.mx) ans.cnt += a.cnt;
		else ans.smx = max(ans.smx, a.mx);
		if(b.mx == ans.mx) ans.cnt += b.cnt;
		else ans.smx = max(ans.smx, b.mx);

		return ans;
	}
	vector<node> st;

	void build(int p, int L, int R) {
		if(L == R) {
			st[p] = {oo, oo, -oo, 1};
			return;
		}
		int mid = (L + R) / 2;
		build(2 * p, L, mid);
		build(2 * p + 1, mid + 1, R);
		st[p] = comb(st[2 * p], st[2 * p + 1]);
	}

	void propmx(int p, int L, int R) {
		if(L == R) return;
		if(st[p].mx < st[2 * p].mx) {
			st[2*p].sum -= 1LL*(st[2*p].mx - st[p].mx) * st[2*p].cnt;
			st[2 * p].mx = st[p].mx;
		}
		if(st[p].mx < st[2 * p + 1].mx) {
			st[2*p+1].sum -= 1LL*(st[2*p+1].mx-st[p].mx)*st[2*p+1].cnt;
			st[2 * p + 1].mx = st[p].mx;
		}
	}

	void updmin(int p, int L, int R, int i, int j, int x) {
		if(i > R or j < L) return;
		if(st[p].mx <= x) return;
		if(L >= i and R <= j and st[p].smx < x) {
			st[p].sum -= 1LL * (st[p].mx - x) * st[p].cnt;
			st[p].mx = x;
			return;
		}
		propmx(p, L, R);
		int mid = (L + R) / 2;
		updmin(2 * p, L, mid, i, j, x);
		updmin(2 * p + 1, mid + 1, R, i, j, x);
		st[p] = comb(st[2 * p], st[2 * p + 1]);
	}

	ll querysum(int p, int L, int R, int i, int j) {
		if(i > R or j < L) return 0;
		if(L >= i and R <= j) return st[p].sum;
		propmx(p, L, R);
		int mid = (L + R) / 2;
		return querysum(2 * p, L, mid, i, j) +
			   querysum(2 * p + 1, mid + 1, R, i, j);
	}

	void upd(int p, int L, int R, int i, int val) {
		if(i < L or i > R) return;
		if(L == R) {
			st[p].sum = val;
			st[p].cnt = 1;
			st[p].mx = val;
			return;
		}
		propmx(p, L, R);
		int mid = (L + R) / 2;
		upd(2 * p, L, mid, i, val);
		upd(2 * p + 1, mid + 1, R, i, val);
		st[p] = comb(st[2 * p], st[2 * p + 1]);
	}
	SegBeats(int sz) : n(sz), st(4*sz) {
		build(1, 1, n);
	}
	void upd(int i, int val) {
		upd(1, 1, n, i, val);
	}
	// make a[id] = min(a[id], x) for i in [i, j]
	void updmin(int i, int j, int x) {
		updmin(1, 1, n, i, j, x);
	}
	ll querysum(int i, int j) {
		return querysum(1, 1, n, i, j);
	}
};

vector<int> go[N];
vector<int> ft[N];

void prec_add(int x, int y) {
	for(; x < N; x += x & -x) {
		go[x].push_back(y);
	}
}
void init() {
	for(int i = 1; i < N; i++) {
		sort(go[i].begin(), go[i].end());
		ft[i].assign(go[i].size() + 1, 0);
	}
}
void add(int x, int y, int val) {
	for(; x < N; x += x & -x) {
		int id = int(upper_bound(go[x].begin(), go[x].end(), y) - go[x].begin());
		for(; id < (int)ft[x].size(); id += id & -id)
			ft[x][id] += val;
	}
}
int sum(int x, int y) {
	int ans = 0;
	for(; x > 0; x -= x & -x) {
		int id = int(upper_bound(go[x].begin(), go[x].end(), y) - go[x].begin());
		for(; id > 0; id -= id & -id)
			ans += ft[x][id];
	}
	return ans;
}

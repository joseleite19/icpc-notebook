// source: https://github.com/tfg50/Competitive-Programming/

template <class Info = int>
class ColorUpdate {
	set<Range> ranges;
public:
	struct Range {
		Range(int a = 0) : l(a) {}
		Range(int a, int b, Info c) : l(a), r(b), v(c) {}
		int l, r;
		Info v;
		bool operator<(const Range &b) const { return l < b.l; }
	};
	vector<Range> upd(int l, int r, Info v) {
		vector<Range> ans;
		if(l >= r) return ans;
		auto it = ranges.lower_bound(l);
		if(it != ranges.begin()) {
			it--;
			if(it->r > l) {
				auto cur = *it;
				ranges.erase(it);
				ranges.emplace(cur.l, l, cur.v);
				ranges.emplace(l, cur.r, cur.v);
			}
		}
		it = ranges.lower_bound(r);
		if(it != ranges.begin()) {
			it--;
			if(it->r > r) {
				auto cur = *it;
				ranges.erase(it);
				ranges.emplace(cur.l, r, cur.v);
				ranges.emplace(r, cur.r, cur.v);
			}
		}
		for(it = ranges.lower_bound(l); it != ranges.end() && it->l < r; it++) {
			ans.push_back(*it);
		}
		ranges.erase(ranges.lower_bound(l), ranges.lower_bound(r));
		ranges.emplace(l, r, v);
		return ans;
	}
};

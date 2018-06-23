class minQ{
	deque<tuple<int, int, int> > p;
	int delta, sz;
public:
	minQ() : delta(0), sz(0) {}

	inline int size() const{ return sz; }
	inline void add(int x){ delta += x; }
	inline void push(int x, int id){
		x -= delta;
		int t = 1;
		while(p.size() > 0 && get<0>(p.back()) >= x)
			t += get<1>(p.back()), p.pop_back();
		p.emplace_back(x, t, id);
		sz++;
	}
	inline void pop(){
		get<1>(p.front())--;
		if(!get<1>(p.front())) p.pop_front();
		sz--;
	}
	inline int getmin() const{ return get<0>(p.front()) + delta; }
	inline int getid() const{ return get<2>(p.front()); }
};

template<typename T>
class minQ{
	deque<tuple<T, int, int> > p;
	T delta;
	int sz;
public:
	minQ() : delta(0), sz(0) {}
	inline int size() const{ return sz; }
	inline void add(T x){ delta += x; }
	inline void push(T x, int id){
		x -= delta, sz++;
		int t = 1;
		while(p.size() > 0 && get<0>(p.back()) >= x)
			t += get<1>(p.back()), p.pop_back();
		p.emplace_back(x, t, id);
	}
	inline void pop(){
		get<1>(p.front())--, sz--;
		if(!get<1>(p.front())) p.pop_front();
	}
	T getmin() const{ return get<0>(p.front())+delta; }
	int getid() const{ return get<2>(p.front()); }
};

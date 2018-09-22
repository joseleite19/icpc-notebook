template<typename T>
class wavelet{
    T L, R;
    vector<int> l;
	vector<T> sum; // <<
	wavelet *lef, *rig;

	int r(int i) const{ return i - l[i]; }

public:
	template<typename ITER>
    wavelet(ITER bg, ITER en){
		lef = rig = nullptr;
        L = *bg, R = *bg;

		for(auto it = bg; it != en; it++)
            L = min(L, *it), R = max(R, *it);
		if(L == R) return;
        
        T mid = L + (R - L)/2;
		l.reserve(std::distance(bg, en) + 1);
		sum.reserve(std::distance(bg, en) + 1);
		l.push_back(0), sum.push_back(0);
		for(auto it = bg; it != en; it++)
			l.push_back(l.back() + (*it <= mid)),
			sum.push_back(sum.back() + *it);

		auto tmp = stable_partition(bg, en, [mid](T x){
			return x <= mid;
		});

		if(bg != tmp) lef = new wavelet(bg, tmp);
		if(tmp != en) rig = new wavelet(tmp, en);
    }

	~wavelet(){
		delete lef;
		delete rig;
	}
    
	// 1 index, first is 1st
    T kth(int i, int j, int k) const{
        if(L >= R) return L;
        int c = l[j] - l[i-1];
        if(c >= k) return lef->kth(l[i-1]+1, l[j], k);
        else return rig->kth(r(i-1)+1, r(j), k - c);
    }
	
	// # elements > x on [i, j]
	int cnt(int i, int j, T x) const{
		if(L > x) return j - i + 1;
		if(R <= x || L == R) return 0;
		int ans = 0;
		if(lef) ans += lef->cnt(l[i-1]+1, l[j], x);
		if(rig) ans += rig->cnt(r(i-1)+1, r(j), x);
		return ans;
	}

	// sum of elements <= k on [i, j]
	T sumk(int i, int j, T k){
        if(L == R) return R <= k ? L * (j - i + 1) : 0;
		if(R <= k) return sum[j] - sum[i-1];
		int ans = 0;
		if(lef) ans += lef->sumk(l[i-1]+1, l[j], k);
		if(rig) ans += rig->sumk(r(i-1)+1, r(j), k);
		return ans;
	}

	// swap (i, i+1) just need to update "array" l[i]
};

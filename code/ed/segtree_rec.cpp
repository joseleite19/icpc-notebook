class  SegTree{
    vi st;
    vi lazy;
    int size;

    int el_neutro = -oo;

    inline int f(int a, int b){
        return max(a,b);
    }
    inline int left(int i) {return 2 * i + 1;};
    inline int right(int i) {return 2 * i + 2;};
    void build(int sti, int stl, int str, vi& nums) {
        if(stl == str) {
            st[sti] = nums[stl];
            return;
        }
        int mid = (stl + str) / 2;
        build(left(sti), stl, mid, nums);
        build(right(sti), mid + 1, str, nums);
        st[sti] = f(st[left(sti)], st[right(sti)]);
    }

    void propagate(int sti, int stl, int str){
        if(lazy[sti]){
            st[sti] += lazy[sti];
            if(stl != str)
            {
                lazy[left(sti)] += lazy[sti];
                lazy[right(sti)] += lazy[sti];
            }
            lazy[sti] = 0;
        }
    }
    int query(int sti, int stl, int str, int l, int r){
        propagate(sti, stl, str);

        if(str < l || r < stl)
            return el_neutro;


        if(stl >= l and str <= r)
            return st[sti];

        int mid = (str+stl)/2;

        return f(query(left(sti),stl,mid,l,r),query(right(sti),mid+1,str,l,r));
    }
    void update_range(int sti, int stl, int str, int l,int r, int amm){
        propagate(sti, stl, str);
        if(stl >= l and str <= r){
            lazy[sti] = amm;
            propagate(sti, stl, str);
            return;
        }
        if(stl > r  or str < l)
            return;
        int mid = (stl + str)/2;
        update_range(left(sti),stl,mid,l,r,amm);
        update_range(right(sti),mid+1,str,l,r,amm);
        st[sti] = f(st[left(sti)],st[right(sti)]);
    }
    void update(int sti, int stl, int str, int i, int amm){
        propagate(sti, stl, str);
        if(stl == i and str == i){
            st[sti] = amm;
            return;
        }
        if(stl > i or str < i)
            return;
        int mid = (stl + str)/2;
        update(left(sti),stl,mid,i,amm);
        update(right(sti),mid+1,str,i,amm);
        st[sti] = f(st[left(sti)],st[right(sti)]);
    }
    public:
        SegTree(vi& v) : st(4*v.size(),0), lazy(4*v.size(),0) {size = v.size(); build(0,0,size - 1, v);}
        SegTree(int n) : st(4*n,0), lazy(4*n,0){size = n;}
        int query(int l, int  r){return query(0,0,size-1,l,r);}
        void update_range(int l, int r, int amm){update_range(0,0,size-1,l,r,amm);}
        void update(int i, int amm){update(0,0,size-1,i,amm);}
};

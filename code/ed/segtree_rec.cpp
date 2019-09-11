class  SegTree{
    vi st;
    vi lazy;
    int size;

    int el_neutro = -oo;

    int f(int a, int b){
        return max(a,b);
    }
    void propagate(int sti, int stl, int str){
        if(lazy[sti]){
            st[sti] += lazy[sti];
            if(stl != str)
            {
                lazy[sti*2 + 1] += lazy[sti];
                lazy[sti*2 + 2] += lazy[sti];
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

        return f(query(sti*2+1,stl,mid,l,r),query(sti*2+2,mid+1,str,l,r));
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
        update_range(sti*2+1,stl,mid,l,r,amm);
        update_range(sti*2+2,mid+1,str,l,r,amm);
        st[sti] = f(st[sti*2+1],st[sti*2+2]);
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
        update(sti*2+1,stl,mid,i,amm);
        update(sti*2+2,mid+1,str,i,amm);
        st[sti] = f(st[sti*2+1],st[sti*2+2]);
    }
    public:
        SegTree(int n):  st(4*n,0), lazy(4*n,0){size = n;}
        int query(int l, int  r){return query(0,0,size-1,l,r);}
        void update_range(int l, int r, int amm){update_range(0,0,size-1,l,r,amm);}
        void update(int i, int amm){update(0,0,size-1,i,amm);}
};
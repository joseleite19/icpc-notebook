struct Segtree{
    int n;
    vector<ll> st, lazy;

    void prop(int p, int L, int R){
        if(lazy[p]){
            st[p] += lazy[p] * (R - L + 1);
            if(L != R) lazy[2*p] += lazy[p], lazy[2*p+1] += lazy[p];
            lazy[p] = 0;
        }
    }

    void update(int p, int L, int R, int i, int j, ll v){
        prop(p, L, R);
        if(L > j || R < i) return;
        if(L >= i && R <= j){
            lazy[p] = v;
            prop(p, L, R);
            return;
        }
        int mid = (L+R)/2;
        update(2*p, L, mid, i, j, v);
        update(2*p+1, mid+1, R, i, j, v);
        st[p] = st[2*p] + st[2*p+1];
    }
    ll query(int p, int L, int R, int i, int j){
        prop(p, L, R);
        if(L > j || R < i) return 0;
        if(L >= i && R <= j) return st[p];
        int mid = (L+R)/2;
        return query(2*p, L, mid, i, j) + query(2*p+1, mid+1, R, i, j);
    }
public:
    Segtree(int sz = 0) : n(sz), st(4*sz, 0), lazy(4*sz, 0){}

    // sum v to every element in range [i, j]
    void update(int i, int j, ll v){
        update(1, 1, n, i, j, v);
    }
    ll query(int i, int j){
        return query(1, 1, n, i, j);
    }
};


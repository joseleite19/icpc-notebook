struct Segtree{
    int n;
    vector<int> st;

    void build(int p, int L, int R, const int v[]){
        if(L == R){ st[p] = v[L]; return; }
        int mid = (L + R) / 2;
        build(2*p, L, mid, v);
        build(2*p+1, mid+1, R, v);
        st[p] = max(st[2*p], st[2*p+1]);
    }
    int findL(int p, int i, int L, int R, int v){
        if(i <= L || v >= st[p]) return -1;
        if(L == R) return L;

        int mid = (L + R) / 2;
        int ret = -1;
        if(i > mid+1 && st[2*p+1] > v)
            ret = findL(2*p+1, i, mid+1, R, v);
        if(ret != -1) return ret;
        return findL(2*p, i, L, mid, v);
    }

    int findR(int p, int i, int L, int R, int v){
        if(i > R || v >= st[p]) return -1;
        if(L == R) return L;

        int mid = (L + R) / 2;
        int ret = -1;
        if(i < mid && st[2*p] > v)
            ret = findR(2*p, i, L, mid, v);
        if(ret != -1) return ret;
        return findR(2*p+1, i, mid+1, R, v);
    }

    public:
    Segtree(int sz, const int v[]) : n(sz), st(4*sz, 0){
        build(1, 0, n-1, v);
    }
    int findR(int i, int v){
        return findR(1, i, 0, n-1, v);
    }
    int findL(int i, int v){
        return findL(1, i, 0, n-1, v);
    }
};


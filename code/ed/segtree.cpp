T query(int l, int r, int &pos){ // [l, r]
    T rl, rr;
    for(l += n, r += n+1; l < r; l >>= 1, r >>= 1){
        if(l & 1) rl = merge(rl, st[l++]);
        if(r & 1) rr = merge(st[--r], rr);
    }
    return merge(rl, rr);
}

// initially save v[i] in st[n+i] for all i in [0, n)
void build(){
    for(int p = n-1; p > 0; p--)
        st[p] = merge(st[2*p], st[2*p+1]);
}

void update(int p, T val){
    st[p += n] = val;
    while(p >>= 1) st[p] = merge(st[2*p], st[2*p+1]);
}


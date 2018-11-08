void add_line(line nw, int v = 1, int l = 0, int r = maxn) { // [l, r)
    int m = (l + r) / 2;
    bool lef = nw.eval(l) < st[v].eval(l);
    bool mid = nw.eval(m) < st[v].eval(m);
    if(mid) swap(st[v], nw);
    if(r - l == 1) {
        return;
    } else if(lef != mid) {
        add_line(nw, 2 * v, l, m);
    } else {
        add_line(nw, 2 * v + 1, m, r);
    }
}

int get(int x, int v = 1, int l = 0, int r = maxn) {
    int m = (l + r) / 2;
    if(r - l == 1) {
        return st[v].eval(x);
    } else if(x < m) {
        return min(st[v].eval(x), get(x, 2*v, l, m));
    } else {
        return min(st[v].eval(x), get(x, 2*v+1, m, r));
    }
}


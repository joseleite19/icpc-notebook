void cnt_sz(int u, int p = -1){
    sz[u] = 1;
    for(int v : g[u]) if(v != p)
        cnt_sz(v, u), sz[u] += sz[v];
}
void add(int u, int p, int big = -1){
    // Update info about this vx in global answer
    for(int v : g[u]) if(v != p && v != big)
        add(v, u);
}
void dfs(int u, int p, int keep){
    int big = -1, mmx = -1;
    for(int v : g[u]) if(v != p && sz[v] > mmx)
        mmx = sz[v], big = v;
    for(int v : g[u]) if(v != p && v != big)
        dfs(v, u, 0);
    if(big != -1) dfs(big, u, 1);
    add(u, p, big);
    for(auto x : q[u]){
        // answer all queries for this vx
    }
    if(!keep){ /*Remove data from this subtree*/ }
}


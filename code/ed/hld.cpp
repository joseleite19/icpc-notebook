void dfs_sz(int u){
    sz[u] = 1;
    for(int &v : g[u]) if(v == p[u]){
        swap(v, g[u].back()); g[u].pop_back();
        break;
    }
    for(int &v : g[u]){
        p[v] = u; dfs_sz(v); sz[u] += sz[v];
        if(sz[v] > sz[ g[u][0] ])
            swap(v, g[u][0]);
    }
}
// nxt[u] = start of path with u
// set nxt[root] = root beforehand
void dfs_hld(int u){
    in[u] = dfst++;
    rin[in[u]] = u;
    for(int v : g[u]){
        nxt[v] = (v == g[u][0] ? nxt[u] : v); dfs_hld(v);
    }
    out[u] = dfst;
}
// subtree of u => [ in[u], out[u] )
// path from nxt[u] to u => [ in[ nxt[u] ], in[u] ]

int start[N], dfs_time;
int tour[2*N], id[2*N];

void dfs(int u){
    start[u] = dfs_time;
    id[dfs_time] = u;
    tour[dfs_time++] = start[u];
    for(int v : g[u]){
        dfs(v);
        id[dfs_time] = u;
        tour[dfs_time++] = start[u];
    }
}

int LCA(int u, int v){
    if(start[u] > start[v]) swap(u, v);
    return id[min(tour[k]for k in [start[u],start[v]])];
}


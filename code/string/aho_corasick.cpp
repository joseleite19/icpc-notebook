int to[N][A];
int ne = 2, fail[N], term[N];
void add_string(const char *str, int id){
    int p = 1;
    for(int i = 0; str[i]; i++){
        int ch = str[i] - 'a';
        if(!to[p][ch]) to[p][ch] = ne++;
        p = to[p][ch];
    }
    term[p]++;
}
void init(){
    for(int i = 0; i < ne; i++) fail[i] = 1;
    queue<int> q; q.push(1);
    int u, v; char c;
    while(!q.empty()){
        u = q.front(); q.pop();
        for(int i = 0; i < A; i++){
            if(to[u][i]){
                v = to[u][i]; q.push(v);
                if(u != 1){
                    fail[v] = to[ fail[u] ][i];
                    term[v] += term[ fail[v] ];
                }
            }
            else if(u != 1) to[u][i] = to[ fail[u] ][i];
            else to[u][i] = 1;
        }
    }
}
void clean() {
    memset(to, 0, ne * sizeof(to[0]));
    memset(fail, 0, ne * sizeof(fail[0]));
    memset(term, 0, ne * sizeof(term[0]));
    memset(to, 0, ne * sizeof(to[0]));
    ne = 2;
}

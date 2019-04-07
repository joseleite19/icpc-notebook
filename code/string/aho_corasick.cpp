map<char, int> to[N];
int ne = 2, term[N], fail[N];
void add_string(char *str){
    int p = 1;
    for(int i = 0; str[i]; i++){
        if(!to[p][ str[i] ]) to[p][ str[i] ] = ne++;
        p = to[p][ str[i] ];
    }
    term[p] = 1;
}
int go(int s, char c){
    while(s && !to[s].count(c)) s = fail[s];
    if(to[s].count(c)) return to[s][c];
    return s;
}
void init(){
    queue<int> q; q.push(1);
    int u, v; char c;
    while(!q.empty()){
        u = q.front(); q.pop();
        for(auto w : to[u]){
            tie(c, v) = w; q.push(v);
            if(u != 1){
                fail[v] = go(fail[u], c);
                term[v] |= term[ fail[v] ];
            }
        }
    }
}


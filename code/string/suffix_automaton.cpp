map<char, int> to[2*N];
int link[2*N], len[2*N], last = 0, sz = 1;

void add_letter(char c){
    int p = last;
    last = sz++;
    len[last] = len[p] + 1;
    for(; !to[p][c]; p = link[p]) to[p][c] = last;
    if(to[p][c] == last){
        link[last] = 0;
        return;
    }
    int u = to[p][c];
    if(len[u] == len[p]+1){
        link[last] = u;
        return;
    }
    int c1 = sz++;
    to[c1] = to[u];
    link[c1] = link[u];
    len[c1] = len[p]+1;
    link[last] = link[u] = c1;
    for(; to[p][c] == u; p = link[p]) to[p][c] = c1;
}


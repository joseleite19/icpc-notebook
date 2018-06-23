#include <bits/stdc++.h>

using namespace std;

int pX[200200], pY[200200], distX[200200], distY[200200];
int n, ptrx = 1, ptry = 100100;

vector<vector<int> > g(200200);

bool bfs(){
    bool found = false;
    queue<int> Q;

    for(int i = 1; i < ptrx; i++)
        if(pX[i] == -1)
            Q.push(i);

    memset(distX, 0, sizeof distX);
    memset(distY, 0, sizeof distY);

    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        for(int i = 0; i < (int)g[u].size(); i++){
            int v = g[u][i];
            if(distY[v] == 0){
                distY[v] = distX[u]+1;
                if(pY[v] == -1) found = true;
                else{
                    distX[ pY[v] ] = distY[v]+1;
                    Q.push(pY[v]);
                }
            }
        }
    }
    return found;
}

bool dfs(int u){
    for(int i = 0; i < (int)g[u].size(); i++){
        int v = g[u][i];
        if(distX[u]+1 == distY[v]){
            distY[v] = 0; // "apaga" o vertice para a dfs
            if(pY[v] == -1 || dfs(pY[v])){
                pX[u] = v, pY[v] = u;
                return true;
            }
        }
    }
    return false;
}

int f(){
    int ans = 0;
    memset(pX, -1, sizeof pX);
    memset(pY, -1, sizeof pY);

    while(bfs())
        for(int i = 1; i < ptrx; i++)
            if(pX[i] == -1 && dfs(i)) // eh possivel escolher um par para i
                ans++;

    return ans;
}

int main(){
    int x, y;

    map<int, int> mapx;
    map<int, int> mapy;

    while(scanf("%d", &n) == 1){
        g.assign(200200, vector<int>());

        for(int i = 0; i < n; i++){
            scanf("%d %d", &x, &y);

            if(mapx.find(x) == mapx.end()) mapx[x] = ptrx++;
            if(mapy.find(y) == mapy.end()) mapy[y] = ptry++;

            x = mapx[x];
            y = mapy[y];

            g[x].push_back(y);
            g[y].push_back(x);
        }

        printf("%d\n", f());
    }
    return 0;
}
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
 
using namespace std;
int v[100005];
int seg[4000005];
int seg2[4000005];
 
int esquerda(int p){
    return 2 * p;
}
 
int direita(int p){
    return 2 * p + 1;
}

int query(int p, int i, int j, int L, int R){
    if(j < L || i > R) return 1000000000;
    if(i <= L && j >= R) return seg[p];
    int meio = (L + R) / 2;
    return min(query(esquerda(p), i, j, L, meio),
        query(direita(p), i, j, meio + 1, R));
}
 
int findL(int p, int i, int L, int R, int v){
    if(i <= L) return -1;
    if(v >= seg2[p]) return -1;
    if(L == R) return L;
     
    int meio = (L + R) / 2;
    int ret = -1;
    if(i > meio+1 && seg2[direita(p)] > v)
        ret = findL(direita(p), i, meio+1, R, v);
    if(ret != -1) return ret;
    return findL(esquerda(p), i, L, meio, v);
}
 
int findR(int p, int i, int L, int R, int v){
    if(i > R) return -1;
    if(v >= seg2[p]) return -1;
    if(L == R) return L;
     
    int meio = (L + R) / 2;
    int ret = -1;
    if(i < meio && seg2[esquerda(p)] > v)
        ret = findR(esquerda(p), i, L, meio, v);
    if(ret != -1) return ret;
    return findR(direita(p), i, meio+1, R, v);
}
int constructMax(int L, int R, int p){
    if(L == R) return seg2[p] = v[L];
    int mid = (L + R) / 2;
    return seg2[p] = max(constructMax(L, mid, esquerda(p)),
        constructMax(mid+1, R, direita(p)));
}

int constructMin(int L, int R, int p){
    if(L == R) return seg[p] = v[L];
    int mid = (L + R) / 2;
    return seg[p] = min(constructMin(L, mid, esquerda(p)),
        constructMin(mid+1, R, direita(p)));
}

int main(){
    int n;
 
    while(scanf("%d", &n) == 1){
        memset(seg, 0, sizeof(seg));
        memset(seg2, 0, sizeof(seg2));
 
        for(int i = 0; i < n; i++)
            scanf("%d", v + i);

        constructMax(0, n-1, 1);
        constructMin(0, n-1, 1);

        bool first = true, ultra, left, right;
        for(int i = 0; i < n; i++){
            ultra = false;
            if((i == 0 || v[i] > v[i-1]) && (i == n-1 || v[i] > v[i+1])){
                int id = findL(1, i, 0, n-1, v[i]);
                int id2 = findR(1, i, 0, n-1, v[i]);
                if(id == -1 && id2 == -1){
                    if(v[i] >= 150000)
                        ultra = true;
                }
                else{
                    left = false;
                    if(id == -1) left = true;
                    else{
                        int d = query(1, id+1, i-1, 0, n-1);
                        if(v[i] - d >= 150000) left = true;
                    }
                    right = false;
                    if(id2 == -1) right = true;
                    else{
                        int d = query(1, i+1, id2-1, 0, n-1);
                        if(v[i] - d >= 150000) right = true;
                    }
                    if(left && right){
                        ultra = true;
                    }
                }
                if(ultra){
                    if(!first) printf(" ");
                    printf("%d", i+1);
     
                    first = false;
                }
            }
        }
        printf("\n");
    }
 
    return 0;
}
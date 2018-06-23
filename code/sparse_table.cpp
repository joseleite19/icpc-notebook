#include <bits/stdc++.h>

#define mp make_pair
#define ff first
#define ss second

using namespace std;

typedef long long ll;

int st1[200005][20], st2[200005][20];

void build(int n){
    int i,j;
    for(j = 1; 1<<j <= n; j++){
        for(i = 0; i +(1<<j) <= n; i++){
            st1[i][j] = max(st1[i][j-1],st1[i+(1<<(j-1))][j-1]);
            st2[i][j] = min(st2[i][j-1],st2[i+(1<<(j-1))][j-1]);
        }
    }
}

int getA(int l, int r){
    int num = r-l+1,k=0;
    while(num>=2) num/=2, k++;
    return max(st1[l][k], st1[r-(1<<k)+1][k]);
}

int getB(int l, int r){
    int num = r-l+1,k=0;
    while(num>=2) num/=2, k++;
    return min(st2[l][k], st2[r-(1<<k)+1][k]);
}

int bsearch1(int i, int n){
    int mid,l=i-1,r=n;
    while(l+1 < r){
        mid = (l+r)>>1;
        int a = getA(i, mid);
        int b = getB(i, mid);
        if(a < b) l = mid;
        else r = mid;
    }
    return r;
}

int bsearch2(int i, int n){
    int mid,l=i-1,r=n;
    while(l+1 < r){
        mid = (l+r)>>1;
        int a = getA(i, mid);
        int b = getB(i, mid);
        if(a <= b) l = mid;
        else r = mid;
    }
    return r;
}

int main(){
    int n,i,j;

    scanf("%d", &n);
    for(i = 0; i < n; i++) scanf("%d", &st1[i][0]);
    for(i = 0; i < n; i++) scanf("%d", &st2[i][0]);
    build(n);
    ll ans = 0;
    for(i = 0; i < n; i++){
        int x = bsearch1(i,n);
        int y = bsearch2(i,n);
        if(y > x)
            ans += (y-x);
    }
    printf("%lld\n", ans);
 
    return 0;
}

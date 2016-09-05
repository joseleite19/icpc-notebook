#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
#define MOD (100000000)
using namespace std;

int n, m, dp[104][104];
pair <int, int> activity[105];

int f(int prev, int next){
    if(dp[prev][next] != -1) return dp[prev][next];

    if(activity[next].second == m) return 1;

    int aux = 0;
    for(int i = next+1; i < n; i++)
        if(activity[i].first > activity[next].first &&
            activity[i].first <= activity[next].second &&
            activity[i].second > activity[next].second &&
            (prev == next || activity[i].first > activity[prev].second))
            aux = (aux + f(next, i)) % MOD;

    return dp[prev][next] = aux;
}

int main(){

    while(scanf("%d %d", &m, &n) == 2 && n + m){
        for(int i = 0; i < n; i++)
            scanf("%d %d", &activity[i].first, &activity[i].second);

        memset(dp, -1, sizeof dp);
        sort(activity, activity+n);

        int ans = 0;
        for(int i = 0; i < n && activity[i].first == 0; i++)
            ans = (ans + f(i, i)) % MOD;

        printf("%d\n", ans);
    }

    return 0;
}
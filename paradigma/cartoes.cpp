#include <stdio.h>

long long max(long long a, long long b){
    return (a > b ? a : b);
}
long long min(long long a, long long b){
    return (a < b ? a : b);
}

int main(){
    int n, i, j;
    int cards[10005];
    long long dp[10005];

    while(scanf("%d", &n) == 1){
        for(i = 0; i < n; i++)
            scanf("%d", cards + i);

        for(i = 0; i < n; i++)
            dp[i] = max(cards[i], cards[i+1]);

        for(j = 3; j <= n; j++)
            if(j & 1)
                for(i = 0; i < n; i++)
                    dp[i] = min(dp[i], dp[i+1]);
            else
                for(i = 0; i < n; i++)
                    dp[i] = max(cards[i+j-1] + dp[i], cards[i] + dp[i+1]);

        printf("%lld\n", dp[0]);
    }

    return 0;
}
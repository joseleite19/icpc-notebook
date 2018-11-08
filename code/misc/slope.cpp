///By woqja125, contest: Codeforces Round #371 (Div. 1), problem: (C) Sonya and Problem Wihtout a Legend, Accepted, #

#include<stdio.h>
#include<queue>

int main()
{
    int n, t;
    long long ans = 0;
    std::priority_queue<int> Q;
    scanf("%d%d", &n, &t);
    Q.push(t);
    for(int i=1; i<n; i++)
    {
        scanf("%d", &t); t-=i;
        Q.push(t);
        if(Q.top() > t)
        {
            ans += Q.top() - t;
            Q.pop();
            Q.push(t);
        }
    }
    printf("%lld", ans);
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

void suf_array(char s[], int n, int a[]){

    int c[n];
    int c1[n];
    int a1[n];
    int head[300];
    int cnt[300];
    memset(cnt, 0, sizeof cnt);

    for(int i = 0; i < n; i++) {
        c[i] = s[i];
        cnt[c[i]]++;
    }

    int sum = 0;
    for(int i = 0; i < 300; i++){
        head[i] = sum;
        sum += cnt[i];
    }

    for(int i = 0; i < n; i++) {
        a[head[c[i]]++] = i;
    }

    sum = 0;
    for(int i = 0; i < 300; i++){
        head[i] = sum;
        sum += cnt[i];
    }

    int L = 1;

    while(L < n) {
        cout << "UE " << L << endl;
        for(int i = 0; i < n; i++) {
            int j = (a[i] - L + n) % n;
            cout << "AA " << head[c[j]] << endl;
            a1[head[c[j]]++] = a[i];
        }
        int cc = 0;
        for(int i = 0 ; i < n; i++) {
            if(i == 0 || c[a1[i]] != c[a1[i-1]] || c[(a[i] + L) % n] != c[(a[i] + L + 1) % n]) {
                head[cc] = i;
                c1[a1[i]] = cc;
                cc++;
            } else {
                c1[a1[i]] = c[a1[i - 1]];
            }
        }

        memcpy(a, a1, sizeof a1);
        memcpy(c, c1, sizeof c1);
        L *= 2;
    }
}

int main(){
    char s[1000];
    scanf("%s", s);
    int n = strlen(s);
    int a[1000];
    suf_array(s, n + 1, a);
    for(int i = 0; i < n; i++){
        printf("%s\n", s + a[i] );
    }
    printf("\n");
}
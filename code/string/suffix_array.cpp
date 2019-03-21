int lcp[N], c[N];

// Caractere final da string '\0' esta sendo considerado parte da string s
void build_sa(char s[], int n, int a[]){
    const int A = 300; // Tamanho do alfabeto
    int c1[n], a1[n], h[n + A];
    memset(h, 0, sizeof h);

    for(int i = 0; i < n; i++) {
        c[i] = s[i];
        h[c[i] + 1]++;
    }

    partial_sum(h, h + A, h);
    for(int i = 0; i < n; i++)
        a[h[c[i]]++] = i;
    for(int i = 0; i < n; i++)
        h[c[i]]--;

    for(int L = 1; L < n; L <<= 1) {
        for(int i = 0; i < n; i++) {
            int j = (a[i] - L + n) % n;
            a1[h[c[j]]++] = j;
        }
        
        int cc = -1;
        for(int i = 0; i < n; i++) {
            if(i == 0 || c[a1[i]] != c[a1[i-1]] || c[(a1[i] + L) % n] != c[(a1[i-1] + L) % n])
                h[++cc] = i;
            c1[a1[i]] = cc;
        }

        memcpy(a, a1, sizeof a1);
        memcpy(c, c1, sizeof c1);

        if(cc == n-1) break;
    }
}

void build_lcp(char s[], int n, int a[]){ // lcp[i] = lcp(s[:i], s[:i+1])
    int k = 0;

    //memset(lcp, 0, sizeof lcp);
    for(int i = 0; i < n; i++){
        if(c[i] == n-1) continue;
        int j = a[c[i]+1];
        while(i+k < n && j+k < n && s[i+k] == s[j+k]) k++;
        lcp[c[i]] = k;
        if(k) k--;
    }
}

int comp_lcp(int i, int j){
    if(i == j) return n - i;
    if(c[i] > c[j]) swap(i, j);
    return min(lcp[k] for k in [c[i], c[j]-1]);
}
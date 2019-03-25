// Compute (1*2*...*(p-1)*1*(p+1)*(p+2)*..*n) % p
// in O(p*lg(n))
int factmod(int n, int p){
    int ans = 1;
    while(n > 1){
        for(int i = 2; i <= n % p; i++)
            ans = (ans * i) % p;
        n /= p;
        if(n % 2) ans = p - ans;
    }
    return ans % p;
}
int fac_pow(int n, int p){
    int ans = 0;
    while(n) n /= p, ans += n;
    return ans;
}
int C(int n, int k, int p){
    if(fac_pow(n, p) > fac_pow(n-k, p) + fac_pow(k, p))
        return 0;
    int tmp = factmod(k, p) * factmod(n-k, p) % p;
    return (f_exp(tmp, p - 2, p) * factmod(n, p)) % p;
}

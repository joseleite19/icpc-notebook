struct triple {
    int i, j, k;
    triple() {}
    triple(int i, int j, int k) : i(i), j(j), k(k) {}
};
int cmp(ld x, ld y = 0, ld tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1; }
 
//Problema se tiver mais de uma triangulacao possivel
vector<triple> delaunayTriangulation(vector<ld>& x, vector<ld>& y) {
    int n = x.size();
    vector<ld> z(n);
    vector<triple> ret;
    for (int i = 0; i < n; i++)
        z[i] = x[i] * x[i] + y[i] * y[i];
    rep(i,0,n-2) rep(j,i+1,n) rep(k,i+1,n){
        if (j == k) continue;
        ld xn = (y[j]-y[i])*(z[k]-z[i]) - (y[k]-y[i])*(z[j]-z[i]);
        ld yn = (x[k]-x[i])*(z[j]-z[i]) - (x[j]-x[i])*(z[k]-z[i]);
        ld zn = (x[j]-x[i])*(y[k]-y[i]) - (x[k]-x[i])*(y[j]-y[i]);
        bool flag = (cmp(zn) < 0);
        for (int m = 0; flag && m < n; m++)
            flag &= (cmp((x[m]-x[i])*xn + (y[m]-y[i])*yn + (z[m]-z[i])*zn) <= 0);
        if (flag) ret.push_back(triple(i, j, k));
    }
    return ret;
}

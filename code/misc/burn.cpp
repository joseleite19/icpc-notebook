// count the number of circular arrays of size m, with elements on range [1, c**(n*n)]
int n, m, c; cin >> n >> m >> c;
int x = f_exp(c, n * n); int ans = f_exp(x, m);
for(int i = 1; i <= m; i++) if(m % i == 0) {
  int y = f_exp(x, i);
  for(int j = 1; j < i; j++) if(i % j == 0)
      y = sub(y, mult(j, dp[j]));
  dp[i] = mult(y, inv(i));
  ans = sub(ans, mult(i - 1, dp[i]));
}
cout << ans << '\n';

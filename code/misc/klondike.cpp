// minimum number of moves to make
// all elements equal 
// move: change a segment of equal value
// elements to any value

int v[305], dp[305][305], rec[305][305];

int f(int l, int r){
  if(r == l) return 1;
  if(r < l) return 0;
  if(dp[l][r] != -1) return dp[l][r];
  int ans = f(l+1, r) + 1;
  for(int i = l+1; i <= r; i++)
    if(v[i] == v[l])
      ans = min(ans, f(l, i - 1) + f(i+1, r));
  return dp[l][r] = ans;
}

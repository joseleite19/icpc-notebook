// minimum number of moves to make
// all elements equal 
// move: change a segment of equal value
// elements to any value

int v[305];
int dp[305][305];
int rec[305][305];

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

int main() {
  int n, m;
  memset(dp, -1, sizeof dp);
  scanf("%d %d",&n , &m);
  for(int i = 0; i < n; i++){
    scanf("%d",v+i);
    if(i && v[i] == v[i-1]){
      i--;
      n--;
    }
  }
  printf("%d\n",f(0, n-1) - 1);
  // printf("%d\n",rec[0][n-1] );
  // printf("%d\n",rec[1][n-1] );
  // printf("%d\n",rec[2][n-3] );
}

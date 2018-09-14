// count the number of circular arrays
// of size m, with elements on range
// [1, c**(x*x)]

#include<bits/stdc++.h>
using namespace std;

#define debug(x) cerr << fixed << #x << " = " << x << endl;
#define ll long long

const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;
int dp[MAX];

inline int add(int a, int b) {
  a += b;
  if(a >= MOD) {
    a -= MOD;
  }
  return a;
}

inline int sub(int a, int b) {
  a -= b;
  if(0 > a) {
    a += MOD;
  }
  return a;
}

inline int mult(int a, int b) {
  return (1LL * a * b) % MOD;
}

int f_exp(int x, int exp) {
  if(exp == 0) {
    return 1;
  }
  else if(exp & 1) {
    return mult(x, f_exp(x, exp - 1));
  }
  return f_exp(mult(x, x), exp / 2);
}

inline int inv(int x) {
  return f_exp(x, MOD - 2);
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int n, m, c;
  cin >> n >> m >> c;

  int x = f_exp(c, n * n);
  int ans = f_exp(x, m);
  for(int i = 1; i <= m; i++) {
    if(m % i == 0) {
      int y = f_exp(x, i);
      for(int j = 1; j < i; j++) {
   	    if(i % j == 0) {
          y = sub(y, mult(j, dp[j]));
   	    }
      }
      dp[i] = mult(y, inv(i));
      ans = sub(ans, mult(i - 1, dp[i]));
    }
  }

  cout << ans << '\n';

  return 0;
}

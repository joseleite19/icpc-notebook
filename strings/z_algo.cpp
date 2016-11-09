// Z Algorithm
//
// Given a string s of length N, computes an array z, where z[i] is the length
// of longest substring starting from index i which is also a prefix of s.
// More information: http://codeforces.com/blog/entry/3107
//
// Time complexity: O(N)

void z_algorithm(char *s, int N, int *z) {
  z[0] = N;
  int L = -1, R = -1;

  FOR(i, 1, N) {
    z[i] = i >= R ? 0 : min(R-i, z[i-L]);
    while (i+z[i] < N && s[i+z[i]] == s[z[i]]) ++z[i];
    if (i+z[i] > R) L = i, R = i+z[i];
  }
}
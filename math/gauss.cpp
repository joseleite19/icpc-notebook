// Gaussian elimination
//
// Solves systems of linear equations.
//
// To use, build a matrix of coefficients and call run(mat, R, C).
// If the i-th variable is free, row[i] will be -1, otherwise it's value will
// be ans[i].
//
// Time complexity: O(R * C^2)
//
// Constants to configure:
// - MAXC is the number of columns
// - eps is the epsilon value

namespace Gauss {
  const int MAXC = 1001;

  int row[MAXC];
  double ans[MAXC];
  
  void run(double mat[][MAXC], int R, int C) {
    REP(i, C) row[i] = -1;
    
    int r = 0;
    REP(c, C) {
      int k = r;
      FOR(i, r, R) if (fabs(mat[i][c]) > fabs(mat[k][c])) k = i;
      if (fabs(mat[k][c]) < eps) continue;
      
      REP(j, C+1) swap(mat[r][j], mat[k][j]);
      REP(i, R) if (i != r) {
        double w = mat[i][c] / mat[r][c];
        REP(j, C+1) mat[i][j] -= mat[r][j] * w;
      }
      row[c] = r++;
    }
    
    REP(i, C) {
      int r = row[i];
      ans[i] = r == -1 ? 0 : mat[r][C] / mat[r][i];
    }
  }
}
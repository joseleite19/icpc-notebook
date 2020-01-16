template<typename T, size_t _n, size_t _m>
struct Matrix : std::array<array<T, _n>, _m> { // vector for dynamic size
#define ma(i) this->operator[](i)
#define mat this->_M_elems
  Matrix() {
    for(auto &row : *this) row.fill(0);
  }
  void identity() {
    for(auto &row : *this) row.fill(0);
    for(size_t i = 0; i < _n; i++) mat[i][i] = 1;
  }
  template<size_t _p>
  Matrix<T, _n, _p> operator*(const Matrix<T, _m, _p> &o) const {
    Matrix<T, _n, _p> ans;
    for(size_t i = 0; i < _n; i++) {
      for(size_t k = 0; k < _m; k++) {
        for(size_t j = 0; j < _p; j++) {
          ans[i][j] = ans[i][j] + mat[i][k] * o[k][j];
        }
      }
    }
    return ans;
  }
#undef mat
#undef ma
};

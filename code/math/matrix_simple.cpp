template<size_t _n, size_t _m>
struct Matriz : std::array<array<int, _n>, _m> { // vector for dynamic size
#define ma(i) this->operator[](i)
#define mat this->_M_elems
  Matriz() {
    for(auto &row : *this) row.fill(0);
  }
  void identity() {
    for(auto &row : *this) row.fill(0);
    for(size_t i = 0; i < _n; i++) mat[i][i] = 1;
  }

  template<size_t _p>
  Matriz<_n, _p> operator*(const Matriz<_m, _p> &o) const {
    Matriz<_n, _p> ans;
    for(size_t i = 0; i < _n; i++) {
      for(size_t k = 0; k < _m; k++) {
        for(size_t j = 0; j < _p; j++) {
          ans[i][j] = add(ans[i][j], mul(mat[i][k], o[k][j]));
        }
      }
    }
    return ans;
  }
#undef mat
#undef ma
};

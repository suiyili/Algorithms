#include "matrices/matrix/matrix.hpp"

namespace algebra::matrices {

template <typename T>
class lu_decompose final {
 public:
  explicit lu_decompose(const matrix<T> &equation);

  lu_decompose(const lu_decompose &) = delete;
  lu_decompose(lu_decompose &&) = delete;

  algebra_vector<T> solve(const algebra_vector<T> &equal_to);

 private:
  T &get_value(const pixel &id);
  void init_source(const matrix<T> &source);
  void diagonalize();
  void diagonalize(size_t row);
  void swap_max_below(size_t row);
  void swap_row(size_t row1, size_t row2);

  algebra_vector<T> apply_pivot(const algebra_vector<T> &equal_to);
  algebra_vector<T> forward_substitute(const algebra_vector<T> &equal_to);
  algebra_vector<T> back_substitute(const algebra_vector<T> &forward_substitution);

  const size_t dimensions_;

  std::valarray<T> data_;
  std::valarray<size_t> pivot_;
};

template <typename T>
lu_decompose(const matrix<T> &equation)->lu_decompose<T>;

}  // namespace algebra::matrices
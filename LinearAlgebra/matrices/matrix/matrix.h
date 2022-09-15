#pragma once

#include "generic/algebra_types.hpp"
#include <utility>

#ifdef MATRIX_TEST
#include <catch2/catch_test_macros.hpp>
#endif  // MATRIX_TEST


using namespace algebra::generic;

namespace algebra::matrices {

template <typename T>
class matrix final {
 public:
  using value_type = T;

  matrix(size_t columns, size_t rows);
  explicit matrix(size_t size);
  matrix(std::initializer_list<std::initializer_list<T>> data);
  virtual ~matrix() = default;

  matrix(const matrix &other);
  matrix(matrix &&other) noexcept;

  matrix &operator=(const matrix &other);
  matrix &operator=(matrix &&other);

  size_t rows() const noexcept;
  size_t columns() const noexcept;

  const T &operator[](const pixel &id) const;
  T &operator[](const pixel &id);

  algebra_vector<T> row(size_t ordinal) const;
  algebra_vector<T> column(size_t ordinal) const;

 private:
  static size_t get_columns_count(
      const std::initializer_list<std::initializer_list<T>> &data);
  static size_t get_row_count(
      const std::initializer_list<std::initializer_list<T>> &data);

  const size_t rows_, columns_;
  std::valarray<T> data_;
};

template <typename T>
matrix(std::initializer_list<std::initializer_list<T>> data)->matrix<T>;
matrix(size_t columns, size_t rows)->matrix<double>;
matrix(size_t size)->matrix<double>;

#ifdef MATRIX_TEST

using namespace algebra::matrices;

SCENARIO("matrix test", "[matrix]") {
  GIVEN("invalid init values") {
    WHEN("construct matrix") {
      auto ctor_not_same = [] { matrix mx({{1, 2}, {3}}); };
      auto ctor_empty = [] { matrix<int> mx{}; };
      auto ctor_nest_empty = [] { matrix<float> mx{{}}; };
      auto ctor_invalid_row_column = [] { matrix<int> m(2, 0); };

      THEN("it will throw") {
        REQUIRE_THROWS_AS(ctor_not_same(), std::invalid_argument);
        REQUIRE_THROWS_AS(ctor_empty(), std::invalid_argument);
        REQUIRE_THROWS_AS(ctor_nest_empty(), std::invalid_argument);
        REQUIRE_THROWS_AS(ctor_invalid_row_column(), std::invalid_argument);
      }
    }
  }

  GIVEN("an cell index which is out of size range") {
    matrix mx(3, 2);
    pixel id1{0U, 3U}, id2{3U, 1U};
    WHEN("access cell by the index") {
      THEN("it should throw") {
        REQUIRE_THROWS_AS(mx[id1], std::out_of_range);
        REQUIRE_THROWS_AS(mx[id2], std::out_of_range);
      }
    }
  }

  GIVEN("a cell index which is within the matrix size range") {
    const float expected = 12.5f;
    matrix mx{{1.f, 2.f}, {3.f, expected}};
    pixel id{1U, 1U};
    WHEN("read access by the id") {
      auto actual = mx[id];
      THEN("it will return the actual cell value") {
        REQUIRE(actual == expected);
      }
    }

    AND_WHEN("write access by the id") {
      const auto new_value = 23.4f;
      mx[id] = new_value;
      THEN("it write new value to the cell") { REQUIRE(mx[id] == new_value); }
    }
  }

  GIVEN("a matrix") {
    matrix mx{{1, 2, 3}, {3, 2, 1}, {4, 8, 2}};
    WHEN("access row vector") {
      THEN("it should return the row vector") {
        algebra_vector<decltype(mx)::value_type> expected{1, 2, 3};
        REQUIRE((mx.row(0) == expected).min());
      }
    }

    WHEN("access column vector") {
      THEN("it will return column vector") {
        algebra_vector<decltype(mx)::value_type> expected{2, 2, 8};
        REQUIRE((mx.column(1) == expected).min());
      }
    }
  }
}

#endif  // MATRIX_TEST

}  // namespace algebra::matrices
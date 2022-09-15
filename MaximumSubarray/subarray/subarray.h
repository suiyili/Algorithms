#include <iterator>

namespace generic {
template <typename ITER> class subarray final {
public:
  using value_type = typename std::iterator_traits<ITER>::value_type;

  subarray(ITER begin, ITER end);
  ~subarray() = default;

  subarray(const subarray &other);

  subarray &operator=(const subarray &) = delete;

  const ITER &begin() const;
  const ITER &end() const;
  auto sum() const;

protected:
  static auto sum(ITER begin, ITER end);
  const ITER begin_, end_;
  const value_type sum_;
};

template <typename ITER> subarray(ITER begin, ITER end)->subarray<ITER>;

}
#pragma once

#include <concepts>
#include <iterator>

namespace generic {

template<typename Iterator>
concept RandomAccessIterator = requires(Iterator i, int n) {
  *i;
  *(i + n);
};

template <typename Iterator>
using value_type_t = typename std::iterator_traits<Iterator>::value_type;

template <typename Iterator>
using compare_func = bool (*)(const value_type_t<Iterator> &left,
                              const value_type_t<Iterator> &right);

} // namespace sort_algo
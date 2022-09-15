#pragma once

#include <string_view>
#include <valarray>

namespace pattern_match::kmp {
class kmp_pattern final{
public:
  explicit kmp_pattern(std::string_view pattern);
  typename std::string_view::value_type operator[](size_t i) const;
  size_t size() const;
  size_t prefix(size_t i) const;
private:
  std::string_view pattern_;
  std::valarray<size_t> prefix_;
};
} // namespace pattern_match::kmp

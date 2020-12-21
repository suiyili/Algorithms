#include "kmp_pattern.hpp"

namespace pattern_match::kmp {
kmp_pattern::kmp_pattern(std::string_view pattern) 
: pattern_(pattern), prefix_((size_t)0U, pattern.size() + 1U){
  /* same as kmp search, however,
	treat the pattern string itself as both target and search pattern.
  */
  size_t j = 0;  
  for (size_t i = 1; i < pattern_.size(); ++i) {
    unsigned char k = 1;
    while (pattern_[i] != pattern_[j]) {
      if (j == 0) {
        k = 0;
        break;
      }else
        j = prefix_[j];        
    }
    j += k;
    prefix_[i + 1] = j;
  }
}

typename std::string_view::value_type kmp_pattern::operator[](size_t i) const {
  return pattern_[i];
}

size_t kmp_pattern::size() const { return pattern_.size(); }

size_t kmp_pattern::prefix(size_t i) const { return prefix_[i]; }

} // namespace pattern_match::kmp

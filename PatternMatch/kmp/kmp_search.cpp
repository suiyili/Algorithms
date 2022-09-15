#include "kmp_search.hpp"

namespace pattern_match::kmp {
size_t kmp_search(std::string_view search, const kmp_pattern &pattern) {
  /*
  target t[...], pattern p[...]
  1. p[j-len:j) == p[0:len)
     set prefix[j] = len
     the len of the prefix is also the new starting compare position
  2. if t[i] == p[j], then ++i and ++j.
  3. else since t[i-j:i) == p[0:j), 
  3.1 apply 1 then set j = prefix[j] and goto 2
  
  */
  size_t j = 0;
  for (size_t i = 0; i < search.size(); ++i) {
    unsigned char k = 1;
    while (search[i] != pattern[j]) {
      if (j == 0) {
        k = 0;
        break;
      } else
        j = pattern.prefix(j);
    }
    j += k;
    if (j == pattern.size())
      return i - j + 1;
  }
  return search.size();
}

} // namespace pattern_match::kmp
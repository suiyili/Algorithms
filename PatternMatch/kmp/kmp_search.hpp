#pragma once

#include "kmp/pattern/kmp_pattern.hpp"

namespace pattern_match::kmp {
size_t kmp_search(std::string_view search, const kmp_pattern& pattern);
}
#include "compile_utility.hpp"
#include <cctype>

namespace expression::compile {
bool allow_in_name(char ch) noexcept { return std::isalpha(ch); }
}
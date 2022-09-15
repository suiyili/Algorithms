#include "parse_error.hpp"

namespace expression {
parse_error::parse_error(const std::string &message)
    : std::runtime_error(message) {
}
}


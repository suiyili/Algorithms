#include "algebra_exception.hpp"

namespace algebra {
algebra_exception::algebra_exception(const char *msg)
    : std::runtime_error(msg) {}

algebra_exception::algebra_exception(const std::string &msg)
    : std::runtime_error(msg) {}
}


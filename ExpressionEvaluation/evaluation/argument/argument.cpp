#include "argument.hpp"
#include "generic/parameter_not_set_error/parameter_not_set_error.hpp"
#include <cctype>
#include <sstream>

namespace expression::evaluate {
argument::argument(const std::string_view &arg)
    : arg_(arg) {
  if (arg_.empty())
    throw std::invalid_argument("parameter is null");
}

double argument::result_with(const parameters &params) const {
  double v;
  const std::string arg(arg_);
  if (std::isdigit(arg_.front())) {
    std::string str(arg);
    std::istringstream input(str);
    input >> v;
  } else {
    auto found = params.find(arg.data());
    if (found == params.end())
      throw parameter_not_set_error("parameter is not in the parameter list");
    else
      v = found->second;
  }
  return v;
}

}


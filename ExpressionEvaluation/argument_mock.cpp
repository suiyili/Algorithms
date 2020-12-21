#ifdef TEST

#include "argument_mock.hpp"
#include <sstream>

argument_mock::argument_mock(std::string_view arg)
    : arg_(arg) {}

double argument_mock::result_with(const parameters &params) const {
  auto found = params.find(arg_);
  if (found != params.end())
    return found->second;
  std::istringstream reader(arg_);
  double data;
  reader >> data;
  return data;
}
#endif // TEST
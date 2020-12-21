#pragma once

#include <stdexcept>
#include <string>

namespace algebra {

class algebra_exception : public std::runtime_error {
 public:
  algebra_exception(const char *msg);
  algebra_exception(const std::string &msg);
  virtual ~algebra_exception() override = default;

};

}
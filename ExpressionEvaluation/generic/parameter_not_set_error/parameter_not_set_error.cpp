#include "parameter_not_set_error.hpp"

namespace expression {

parameter_not_set_error::parameter_not_set_error(const std::string &what_arg)
    : logic_error(what_arg) {}
parameter_not_set_error::parameter_not_set_error(const char *what_arg)
    : logic_error(what_arg) {}

}



#include "operand.hpp"

namespace expression::evaluate {
operand::operand(const argument_compilers &compilers)
    : children_(Init(compilers)) {}

double operand::result_with(const parameters &params) const {
  std::valarray<double> args(children_.size());
  size_t j = 0;
  for (auto &i : children_) {
    args[j++] = (i->result_with(params));
  }
  return get_result(args);
}

std::vector<std::unique_ptr<operand_i>> operand::Init(const argument_compilers &compilers) {
  std::vector<std::unique_ptr<operand_i>> children;
  children.reserve(compilers.size());

  for (auto &c : compilers) {
    children.emplace_back(c->compile());
  }
  children.shrink_to_fit();
  return children;
}

}


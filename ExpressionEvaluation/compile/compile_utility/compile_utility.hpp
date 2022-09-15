#pragma once

namespace expression::compile {

constexpr char add_operator = '+',
              subtract_operator = '-',
              multiply_operator = '*',
              divide_operator = '/',
              exponentiate_operator = '^';

bool allow_in_name(char ch) noexcept;
}

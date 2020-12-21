#pragma once

namespace expression::parse {
enum class interval_state : char {
  open = '(',
  semi_close = ',',
  close = ')',
};

constexpr char to_char(interval_state state) noexcept {
  return static_cast<char>(state);
}

}
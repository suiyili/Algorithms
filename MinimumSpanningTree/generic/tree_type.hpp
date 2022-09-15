#pragma once

#include <unordered_set>
#include <utility>
#include "generic/connect/connect.hpp"

namespace std {
using namespace tree::generic;

template <>
struct hash<connect> {
  std::size_t operator()(connect const& conn) const noexcept {
    std::size_t h1 = std::hash<decltype(conn.from())>{}(conn.from());
    std::size_t h2 = std::hash<decltype(conn.to())>{}(conn.to());
    return h1 ^ (h2 << 1);
  }
};
}  // namespace std

namespace tree::generic {

using node_vector = std::pmr::vector<std::size_t>;

}  // namespace tree::generic

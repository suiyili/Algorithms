#pragma once

#include "domain_types.hpp"

namespace bbtree {
enum class item_status : generical::byte {
  none = 0,     // all black
  lchild = 1,   // left child red
  rchild = 2,   // right child red
  children = 3, // both children red
  parent = 4,   // parent red
};
}
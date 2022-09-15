#pragma once

#include <functional>
#include <valarray>
#include <utility>

namespace expression {
template<class T>
constexpr T pi = T(3.1415926535897932385);

using evaluation_function = std::function<double(const std::valarray<double> &)>;
using view_ordinal = std::string_view::size_type;
using view_interval = std::pair<view_ordinal, view_ordinal>;
}
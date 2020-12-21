#pragma once

#include <numeric>

namespace support
{
	template<typename T>
	constexpr T lowest_value = std::numeric_limits<T>::lowest();

	template<typename T>
	constexpr T neutral_value = T(0);
}
#pragma once

#include <stdexcept>

namespace generic
{
	class coprime_error : public std::logic_error
	{
	public:
		using logic_error::logic_error;
	};

}
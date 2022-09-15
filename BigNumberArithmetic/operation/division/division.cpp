#include "division.hpp"
#include <memory>

namespace arithmetic
{
	static bignum divide(const bignum& left, const bignum& right);
	
	bignum operator/(const bignum& left, const bignum& right)
	{
		return divide(left, right);
	}
	
	bignum operator/(const bignum& left, bignum&& right)
	{
		return divide(left, right);
	}
	
	bignum operator/(bignum&& left, const bignum& right)
	{
		return divide(left, right);
	}
	
	bignum operator/(bignum&& left, bignum&& right)
	{
		return divide(left, right);
	}
	
	inline bignum divide(const bignum& left, const bignum& right)
	{
		auto division = left;
		division /= right;
		return std::move(division);
	}
}
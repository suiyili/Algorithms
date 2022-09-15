#include "multiplication.hpp"
#include <memory>

namespace arithmetic
{
	static bignum multiply(const bignum& left, const bignum& right);
	
	bignum operator*(const bignum& left, const bignum& right)
	{
		return multiply(left, right);
	}
	
	bignum operator*(const bignum& left, bignum&& right)
	{
		return multiply(left, right);
	}
	
	bignum operator*(bignum&& left, const bignum& right)
	{
		return multiply(left, right);
	}
	
	bignum operator*(bignum&& left, bignum&& right)
	{
		return multiply(left, right);
	}
	
	inline bignum multiply(const bignum& left, const bignum& right)
	{
		bignum result(left);
		result *= right;
		return std::move(result);
	}
}
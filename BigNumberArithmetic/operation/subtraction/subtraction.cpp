#include "subtraction.hpp"
#include <memory>

namespace arithmetic
{
	static bignum minus(const bignum& left, const bignum& right);
	
	bignum operator-(const bignum& left, const bignum& right)
	{
		return minus(left, right);
	}
	
	bignum operator-(const bignum& left, bignum&& right)
	{
		return minus(left, right);
	}
	
	bignum operator-(bignum&& left, const bignum& right)
	{
		return minus(left, right);
	}
	
	bignum operator-(bignum&& left, bignum&& right)
	{
		return minus(left, right);
	}
	
	inline bignum minus(const bignum& left, const bignum& right)
	{
		auto sum = left;
		sum -= right;
		return std::move(sum);
	}
}


#include "addition.hpp"
#include <memory>

namespace arithmatic
{
	static bignum plus(const bignum& left, const bignum& right);
	
	bignum operator+(const bignum& left, const bignum& right)
	{
		return plus(left, right);
	}
	
	bignum operator+(const bignum& left, bignum&& right)
	{
		return plus(left, right);
	}
	
	bignum operator+(bignum&& left, const bignum& right)
	{
		return plus(left, right);
	}
	
	bignum operator+(bignum&& left, bignum&& right)
	{
		return plus(left, right);
	}
	
	inline bignum plus(const bignum& left, const bignum& right)
	{
		auto sum = left;
		sum += right;
		return std::move(sum);
	}
}
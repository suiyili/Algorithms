#include "modulus.hpp"
#include <memory>

namespace arithmetic
{
	static bignum get_remainder(const bignum& left, const bignum& right);
	
	bignum operator%(const bignum& left, const bignum& right)
	{
		return get_remainder(left, right);
	}
	
	bignum operator%(const bignum& left, bignum&& right)
	{
		return get_remainder(left, right);
	}
	
	bignum operator%(bignum&& left, const bignum& right)
	{
		return get_remainder(left, right);
	}
	
	bignum operator%(bignum&& left, bignum&& right)
	{
		return get_remainder(left, right);
	}
	
	inline bignum get_remainder(const bignum& left, const bignum& right)
	{
		auto remainder = left;
		remainder %= right;
		return std::move(remainder);
	}
}
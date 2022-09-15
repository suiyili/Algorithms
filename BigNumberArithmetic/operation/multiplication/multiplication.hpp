#pragma once

#include "bignum/bignum.hpp"

namespace arithmetic
{
	bignum operator*(const bignum& left, const bignum& right);
	bignum operator*(const bignum& left, bignum&& right);
	bignum operator*(bignum&& left, const bignum& right);
	bignum operator*(bignum&& left, bignum&& right);
}
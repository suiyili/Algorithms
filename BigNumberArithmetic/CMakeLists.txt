cmake_minimum_required()

project(BigNumberArithmetic)

include(../base.cmake)

set(SRC operation/addition/addition.cpp
        bignum/bignum_test.cpp
        generic/bits_value/bits_value_test.cpp
        operation/modulus/modulus.cpp
        operation/operation_test.cpp
        bignum/bignum.cpp
        generic/bits_value/bits_value.cpp
        operation/division/division.cpp
        operation/multiplication/multiplication.cpp
        operation/subtraction/subtraction.cpp
        )
add_executable(BigNumberArithmetic ${SRC})
target(BigNumberArithmetic)
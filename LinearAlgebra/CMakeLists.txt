cmake_minimum_required()
project(LinearAlgebra)

include(../base.cmake)

set(SRC operation/addition/addition.cpp
        generic/algebra_exception/algebra_exception.cpp
        generic/bit_analyzer/bit_analyzer.cpp
        generic/bit_analyzer/bit_analyzer_test.cpp
        operation/determinant/determinant.cpp
        operation/equal/equal.cpp
        operation/exponentiation/exponentiation.cpp
        operation/identity/identity.cpp
        matrices/index_source_matrix/index_source_matrix.cpp
        matrices/index_submatrix/index_submatrix.cpp
        matrices/index_submatrix/index_submatrix_test.cpp
        operation/inverse/inverse.cpp
        matrices/lu_decompose/lu_decompose.cpp
        operation/markov/markov.cpp
        matrices/matrix/matrix.cpp
        operation/multiplication/multiplication.cpp
        operation/operations.cpp
        operation/scalar/scalar.cpp
        operation/subtraction/subtraction.cpp
        operation/transpose/transpose.cpp
        )
add_executable(LinearAlgebra ${SRC})
target(LinearAlgebra)

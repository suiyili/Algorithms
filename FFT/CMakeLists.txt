cmake_minimum_required()
project(FFT)

include(../base.cmake)

set(SRC generic/bit_reverse_array/bit_reverse_array_test.cpp
        generic/complex_matcher/complex_matcher.cpp
        fourier_transform/fourier_transform.cpp
        fourier_transform/fourier_transform_test.cpp
        fourier_transform/inverse_transform/inverse_transform.cpp
        multiplication/multiplication_test.cpp
        fourier_transform/polynomial_transform/polynomial_transform.cpp
        )

add_executable(FFT ${SRC})
target(FFT)
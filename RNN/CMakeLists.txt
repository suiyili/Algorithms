cmake_minimum_required()
project(RNN)

include(../base.cmake)
set(CMAKE_PREFIX_PATH ../../eigen/Eigen3)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

set(RNN_SRC
        generic/rand.hpp
        generic/rand.cpp
        generic/activity.hpp
        generic/utils.hpp
        generic/rnn_type.hpp
        generic/activity.cpp
        generic/utils.cpp
        gru_cell_old.cpp
        sequence_net.hpp
        category_net_test.cpp
        sequence_net_test.cpp
        )
add_executable(RNN ${RNN_SRC})
target(RNN)
target_link_libraries(RNN PRIVATE Eigen3::Eigen)

cmake_minimum_required(VERSION 3.12)
project(ExpressionEvaluation)

set(CMAKE_CXX_STANDARD 17)

include_directories(../Catch2)

aux_source_directory(./ ExpressionEvaluation_SRC)

add_executable(ExpressionEvaluation ${ExpressionEvaluation_SRC})

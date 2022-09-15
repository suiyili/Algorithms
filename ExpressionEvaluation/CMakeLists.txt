cmake_minimum_required()

project(ExpressionEvaluation)

include(../base.cmake)

set(SRC evaluation/operand/addition/addition.cpp
        evaluation/operand/addition/addition_test.cpp
        evaluation/argument/argument.cpp
        compile/operand/argument_compiler/argument_compiler.cpp
        evaluation/operand/mock/argument_compiler_mock/argument_compiler_mock.cpp
        compile/operand/argument_compiler/argument_compiler_test.cpp
        evaluation/operand/mock/argument_mock/argument_mock.cpp
        evaluation/argument/argument_test.cpp
        application/calculator/calculator.cpp
        compile/compile_utility/compile_utility.cpp
        compile/compiler_factory/compiler_factory.cpp
        parse/mock/compiler_factory_mock/compiler_factory_mock.cpp
        parse/mock/compiler_for_parser_mock/compiler_for_parser_mock.cpp
        compile/compiler_mock/compiler_mock.cpp
        evaluation/operand/custom_function/custom_function.cpp
        evaluation/operand/custom_function/custom_function_test.cpp
        evaluation/operand/division/division.cpp
        evaluation/operand/division/division_test.cpp
        evaluation/operand/exponentiation/exponentiation.cpp
        evaluation/operand/exponentiation/exponentiation_test.cpp
        parse/expression_parser/expression_parser.cpp
        parse/expression_parser/expression_parser_test.cpp
        compile/operand/function_compiler/function_compiler.cpp
        compile/operand/function_compiler/function_compiler_test.cpp
        parse/function_parser/function_parser.cpp
        parse/function_parser/function_parser_test.cpp
        application/function_tests.cpp
        evaluation/operand/multiplication/multiplication.cpp
        evaluation/operand/multiplication/multiplication_test.cpp
        evaluation/operand/operand.cpp
        compile/operand/operator_compiler/operator_compiler.cpp
        compile/operand/operator_compiler/operator_compiler_test.cpp
        parse/operator_parser/operator_parser.cpp
        parse/operator_parser/operator_parser_test.cpp
        application/operator_tests.cpp
        generic/parameter_not_set_error/parameter_not_set_error.cpp
        application/parentheses_tests.cpp
        generic/parse_error/parse_error.cpp
        parse/parser_factory/parser_factory.cpp
        parse/mock/parser_factory_mock/parser_factory_mock.cpp
        parse/parser_factory/parser_factory_test.cpp
        parse/mock/parser_mock/parser_mock.cpp
        evaluation/operand/subtraction/subtraction.cpp
        evaluation/operand/subtraction/subtraction_test.cpp
        )

add_executable(ExpressionEvaluation ${SRC})
target(ExpressionEvaluation)
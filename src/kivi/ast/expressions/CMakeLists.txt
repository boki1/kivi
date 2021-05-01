add_library(
        kivi_expressions
        src/kivi_expressions/base.hh
        src/kivi_expressions/base.cc
        src/kivi_expressions/string.hh
        src/kivi_expressions/numerical.hh
        src/kivi_expressions/nop.hh
        src/kivi_expressions/function_call.hh
        src/kivi_expressions/addition.hh
        src/kivi_expressions/negation.hh
        src/kivi_expressions/multiplication.hh
        src/kivi_expressions/division.hh
        src/kivi_expressions/modular_division.hh
        src/kivi_expressions/identifier.hh
        src/kivi_expressions/assignment.hh
        src/kivi_expressions/binary_expression.hh
        src/kivi_expressions/comparison_expression.hh ../stmts/src/kivi_stmts/statement.hh src/kivi_expressions/literal.hh src/kivi_expressions/unary_operation.hh src/kivi_expressions/parameter_list.hh)

target_include_directories(kivi_expressions PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
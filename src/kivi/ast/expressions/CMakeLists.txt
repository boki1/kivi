add_library(
        kivi_expressions
        src/kivi_expressions/base_expression.hh
        src/kivi_expressions/base_expression.cc
        src/kivi_expressions/string.hh
        src/kivi_expressions/numerical.hh
        src/kivi_expressions/nop.hh
        src/kivi_expressions/compound.hh
        src/kivi_expressions/compare_and.hh
        src/kivi_expressions/compare_loop.hh
        src/kivi_expressions/function_call.hh
        src/kivi_expressions/return.hh
        src/kivi_expressions/addition.hh
        src/kivi_expressions/negation.hh
        src/kivi_expressions/multiplication.hh
        src/kivi_expressions/division.hh
        src/kivi_expressions/modular_division.hh
        src/kivi_expressions/identifier.hh
        src/kivi_expressions/copy.hh
        src/kivi_expressions/binary_expression.hh
)

target_include_directories(kivi_expressions PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
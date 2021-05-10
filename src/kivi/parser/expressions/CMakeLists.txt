add_library(
        kivi_expressions
        src/kivi_expressions/base.hh
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
        src/kivi_expressions/binary_operation.hh
        src/kivi_expressions/comparison_operation.hh
        src/kivi_expressions/literal.hh
        src/kivi_expressions/unary_operation.hh
        src/kivi_expressions/parameter_list.hh
        src/kivi_expressions/equality.hh
        src/kivi_expressions/inequality.hh
        src/kivi_expressions/arithmetic_operation.hh
        src/kivi_expressions/sequence.hh)

target_include_directories(kivi_expressions PUBLIC "src")

target_link_libraries(kivi_expressions PRIVATE util)
target_link_libraries(kivi_expressions PRIVATE ast)

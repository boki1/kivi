set(UNIT_TEST_DEPENDS
        catch2
        kivi_parser)

set(UNIT_TEST_TARGET Kivi_Tests)

############################## Main ()

add_library(test_main config.test.cc)
target_link_libraries(test_main PUBLIC ${UNIT_TEST_DEPENDS})

############################## Example test

add_executable(test__example frontend/parse_examples.test.cc)
target_link_libraries(test__example PUBLIC test_main)
add_test(NAME Example
        COMMAND test__example)

############################## Parsing context

add_executable(test__parsing_context frontend/parsing_context.test.cc)
target_link_libraries(test__parsing_context PUBLIC test_main)
add_test(NAME Parsing_context
        COMMAND test__parsing_context)

############################## Expression

add_executable(test__expression frontend/expression.test.cc)
target_link_libraries(test__expression PUBLIC test_main)
add_test(NAME Expression
        COMMAND test__expression)

############################## Parser

add_executable(test__parser frontend/parser.test.cc)
target_link_libraries(test__parser PUBLIC test_main)
add_test(NAME Parser
        COMMAND test__parser)

############################## IR

add_executable(test__ir_gen frontend/ir_generation.test.cc)
target_link_libraries(test__ir_gen PUBLIC test_main)
add_test(NAME IR
        COMMAND test__ir_gen)

############################## x86_64 Machine Target

add_executable(test__x86_64_machine_target backend/x86_64_machine_target.test.cc)
target_link_libraries(test__x86_64_machine_target PUBLIC test_main)
target_link_libraries(test__x86_64_machine_target PUBLIC kivi_compiler)
target_link_libraries(test__x86_64_machine_target PUBLIC kivi_ir)
target_link_libraries(test__x86_64_machine_target PUBLIC arch)
add_test(NAME Machine_Target_x86_64
        COMMAND test__x86_64_machine_target)


############################ x86_64 Instruction Selection
add_executable(test__x86_64_instruction_selection backend/x86_64_instruction_selection.test.cc)
target_link_libraries(test__x86_64_instruction_selection PUBLIC test_main)
target_link_libraries(test__x86_64_instruction_selection PUBLIC kivi_compiler)
target_link_libraries(test__x86_64_instruction_selection PUBLIC kivi_ir)
target_link_libraries(test__x86_64_instruction_selection PUBLIC arch)
add_test(NAME Instruction_Selection_x86_64
        COMMAND test__x86_64_instruction_selection)
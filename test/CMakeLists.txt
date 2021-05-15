set(UNIT_TEST_DEPENDS
        catch2
        kivi_parser)

set(UNIT_TEST_TARGET Kivi_Tests)

############################## Main ()

add_library(test_main main.test.cc)
target_link_libraries(test_main PUBLIC ${UNIT_TEST_DEPENDS})

############################## Example test

add_executable(test__example example.test.cc)
target_link_libraries(test__example PUBLIC test_main)
add_test(NAME Example
        COMMAND test__example)

############################## Configuration test

add_executable(test__config config.test.cc config.test.cc)
target_link_libraries(test__config PUBLIC test_main)
add_test(NAME ConfigCatch2
        COMMAND test__config)

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



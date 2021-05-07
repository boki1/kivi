add_executable(
        example_test
        config_test.cc
        parsing_context_test.cc
)

target_link_libraries(example_test PRIVATE catch2)
target_link_libraries(example_test PRIVATE ast)
target_link_libraries(example_test PRIVATE kivi_expressions)
target_link_libraries(example_test PRIVATE kivi_stmts)
target_link_libraries(example_test PRIVATE kivi_parser)


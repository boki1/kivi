add_executable(
        example_test
        example_test.cc
)

target_link_libraries(example_test PRIVATE catch2)

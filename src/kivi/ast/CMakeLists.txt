add_subdirectory(expressions)

add_library(
        ast
        src/ast/parsing_context.hh
        src/ast/parsing_context.cc
        src/ast/syntax.hh
        src/ast/syntactic_structure.hh
)

target_include_directories(ast PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(ast PRIVATE kivi_expressions)
target_link_libraries(ast PRIVATE kivi_parser)

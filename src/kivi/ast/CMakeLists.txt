add_subdirectory(expressions)
add_subdirectory(stmts)

add_library(
        ast
        src/ast/parsing_context.hh
        src/ast/parsing_context.cc
        src/ast/syntax.hh
        src/ast/syntactic_structure.hh
        src/ast/syntactic_structure.cc
        src/ast/kivi_parser_error.cc
        src/ast/ast.cc
        src/ast/ast.hh)

target_include_directories(ast PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_features(ast PRIVATE cxx_std_17)

target_link_libraries(ast PRIVATE loguru)
target_link_libraries(ast PRIVATE util)
target_link_libraries(ast PRIVATE kivi_stmts)
target_link_libraries(ast PRIVATE kivi_expressions)
target_link_libraries(ast PRIVATE kivi_parser)


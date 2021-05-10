add_subdirectory(expressions)
add_subdirectory(stmts)

add_library(parser
        src/parser/parsing_context.hh
        src/parser/parsing_context.cc
        src/parser/syntax.hh
        src/parser/syntactic_structure.hh
        src/parser/kivi_parser_error.cc
        )

target_include_directories(parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(parser PRIVATE kivi_parser)
target_link_libraries(parser PRIVATE kivi_stmts)
target_link_libraries(parser PRIVATE kivi_expressions)
target_link_libraries(parser PRIVATE util)
target_link_libraries(parser PRIVATE loguru)

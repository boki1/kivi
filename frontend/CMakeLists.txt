add_subdirectory(parser)
add_subdirectory(ir_generation)

############## Parser

set(KIVI_PARSER_FILES
        parser/error.cc
        parser/expressions.cc
        parser/statements.cc
        parser/syntactical_structures.hh
        parser/parsing_context.hh
        parser/parsing_context.cc
        parser/syntax.hh
        parser/syntax.cc
        parser/parser.tab.cc
        parser/parser.tab.hh
        parser/lexer.tab.cc
        )


add_library(kivi_parser "${KIVI_PARSER_FILES}")
add_dependencies(kivi_parser autogen_kivi_parser)
target_include_directories(kivi_parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(kivi_parser PRIVATE loguru)

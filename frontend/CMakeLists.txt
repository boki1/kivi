add_subdirectory(parser)

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

add_library(kivi_ir
        ir_generation/ir_code.hh
        ir_generation/ir_code.cc
        ir_generation/generation_unit.hh
        ir_generation/generation_unit.cc
        ir_generation/generation_context.hh
        ir_generation/generation_context.cc
        )

target_include_directories(kivi_ir PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(kivi_ir PRIVATE kivi_parser)
target_link_libraries(kivi_ir PRIVATE loguru)
target_link_libraries(kivi_ir PRIVATE transform_iterator)

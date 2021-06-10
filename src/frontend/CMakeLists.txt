set(AUTOGEN_PARSER_FILES
        "${PARSER_DIR}/parser.tab.cc"
        "${PARSER_DIR}/parser.tab.hh"
        "${PARSER_DIR}/location.hh"
        )

set(AUTOGEN_LEXER_FILES
        "${PARSER_DIR}/lexer.tab.cc"
        )

set(AUTOGEN_FILES
        "${AUTOGEN_PARSER_FILES}"
        "${AUTOGEN_LEXER_FILES}"
        )

add_custom_command(
        PRE_BUILD
        OUTPUT ${AUTOGEN_PARSER_FILES}
        COMMAND bison "${GRAMMAR}" --file-prefix=parser -d -Wnone
        COMMENT "======================== Generating parser with bison ========================"
        WORKING_DIRECTORY ${PARSER_DIR}
        VERBATIM
)

print(PARSER_DIR)


add_custom_command(
        PRE_BUILD
        OUTPUT ${AUTOGEN_LEXER_FILES}
        COMMAND re2c -is -o lexer.tab.cc "${LEXEMES}"
        COMMENT "========================= Generating lexer with re2c ========================="
        DEPENDS ${AUTOGEN_PARSER_FILES}
        WORKING_DIRECTORY ${PARSER_DIR}
        VERBATIM
)


add_custom_target(autogen_kivi_parser ALL DEPENDS ${AUTOGEN_FILES})

set_source_files_properties("${AUTOGEN_FILES}" PROPERTIES GENERATED TRUE)


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
        ir_generation/codes.cc
        ir_generation/generation_unit.hh
        ir_generation/generation_unit.cc
        ir_generation/generation_context.hh
        ir_generation/concrete_generators.cc
        ir_generation/liveness_data.hh)

target_include_directories(kivi_ir PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(kivi_ir PRIVATE kivi_parser)
target_link_libraries(kivi_ir PRIVATE loguru)
target_link_libraries(kivi_ir PRIVATE transform_iterator)

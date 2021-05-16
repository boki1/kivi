######## Generate parser and lexer with bison and re2c

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
        COMMAND bison "${GRAMMAR}" --file-prefix=parser -d -Wall -Wcex
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


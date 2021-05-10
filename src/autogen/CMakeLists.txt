print(PROJECT_ROOT)
print(AUTOGEN_OUTPUT_DIR)

set(AUTOGEN_PARSER_FILES
        "${AUTOGEN_OUTPUT_DIR}/kivi_parser.tab.cc"
        "${AUTOGEN_OUTPUT_DIR}/kivi_parser.tab.hh"
        "${AUTOGEN_OUTPUT_DIR}/location.hh"
        )

set(AUTOGEN_LEXER_FILES
        "${AUTOGEN_OUTPUT_DIR}/kivi_lexer.tab.cc"
        )

set(AUTOGEN_FILES
        ${AUTOGEN_PARSER_FILES}
        ${AUTOGEN_LEXER_FILES}
        )


add_custom_command(
        PRE_BUILD
        OUTPUT ${AUTOGEN_PARSER_FILES}
        COMMAND bison ${GRAMMAR} --file-prefix=${AUTOGEN_OUTPUT_DIR}/kivi_parser -d -Wnone
        COMMENT "======================== Generating parser with bison ========================"
        WORKING_DIRECTORY ${PROJECT_ROOT}
        VERBATIM
)

add_custom_command(
        PRE_BUILD
        OUTPUT ${AUTOGEN_LEXER_FILES}
        COMMAND re2c -is -o "${AUTOGEN_OUTPUT_DIR}/kivi_lexer.tab.cc" ${LEXEMES}
        COMMENT "========================= Generating lexer with re2c ========================="
        DEPENDS ${AUTOGEN_PARSER_FILES}
        WORKING_DIRECTORY ${PROJECT_ROOT}
        VERBATIM
)


add_custom_target(autogen_kivi_parser ALL DEPENDS ${AUTOGEN_FILES})

set_source_files_properties("${AUTOGEN_FILES}" PROPERTIES GENERATED TRUE)

add_library(kivi_parser "${AUTOGEN_FILES}")

add_dependencies(kivi_parser autogen_kivi_parser)

target_include_directories(kivi_parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(kivi_parser PRIVATE parser)
target_link_libraries(kivi_parser PRIVATE loguru)
target_link_libraries(kivi_parser PRIVATE kivi_expressions)
target_link_libraries(kivi_parser PRIVATE kivi_stmts)

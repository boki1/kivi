###################### Command line interface

add_library(
        cli
        cli/cli.hh
)

target_include_directories(cli PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(cli PRIVATE loguru)

####################### Abstract syntax tree printer

add_library(
        ast_printer
        ast_printer/ast_printer.hh
        ast_printer/ast_printer.cc
)

target_include_directories(ast_printer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}r")
target_link_libraries(ast_printer PRIVATE kivi_parser)
target_link_libraries(ast_printer PRIVATE textbox)

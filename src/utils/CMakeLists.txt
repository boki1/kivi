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

target_include_directories(ast_printer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(ast_printer PRIVATE kivi_parser)
target_link_libraries(ast_printer PRIVATE textbox)


####################### Intermediate code representation printer

add_library(
        ir_printer
        ir_printer/ir_printer.hh
        ir_printer/ir_printer.cc
)

target_include_directories(ir_printer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(ir_printer PRIVATE kivi_ir)

###################### Assembly printer
add_library(
        asm_printer
        asm_printer/asm_printer.cc
        asm_printer/asm_printer.hh
)

target_include_directories(asm_printer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(asm_printer PRIVATE kivi_ir)
target_link_libraries(asm_printer PRIVATE optional_ref)
target_link_libraries(asm_printer PRIVATE kivi_compiler)


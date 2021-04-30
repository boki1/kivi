add_library(
        visitor
        visitor/visitor.hh
        visitor/visitor.cc
        visitor/visitor_element.hh
)

add_library(
        ast_printer
        ast_printer/ast_printer.cc
        ast_printer/ast_printer.hh
)

target_include_directories(visitor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(ast_printer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(
        visitor
        visitor/visitor.hh
        visitor/visitor.cc
        visitor/visitor_element.hh
)

target_include_directories(visitor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(
        ast_printer
        ast_printer/ast_printer.cc
        ast_printer/ast_printer.hh
)

target_include_directories(ast_printer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(
        util
        src/util/common.hh
)

target_include_directories(util PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set_target_properties(util PROPERTIES LINKER_LANGUAGE CXX)


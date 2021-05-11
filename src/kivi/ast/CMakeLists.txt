add_library(ast
        src/ast/ast.cc
        src/ast/ast.hh
        )

target_include_directories(ast PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(ast PRIVATE parser)
target_link_libraries(ast PRIVATE kivi_expressions)
target_link_libraries(ast PRIVATE kivi_stmts)
target_link_libraries(ast PRIVATE util)
target_link_libraries(ast PRIVATE loguru)

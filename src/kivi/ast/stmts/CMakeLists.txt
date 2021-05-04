add_library(
        kivi_stmts
        src/kivi_stmts/statement.hh
        src/kivi_stmts/return.hh
        src/kivi_stmts/while.hh
        src/kivi_stmts/if.hh
        src/kivi_stmts/compound.hh
        src/kivi_stmts/expression.hh
        src/kivi_stmts/var.hh
)

target_include_directories(kivi_stmts PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(kivi_stmts PRIVATE util)
target_link_libraries(kivi_stmts PRIVATE ast)
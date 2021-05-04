add_subdirectory(util)
add_subdirectory(ast)

add_executable(kivi main.cc)

target_link_libraries(kivi PRIVATE kivi_stmts)
target_link_libraries(kivi PRIVATE kivi_expressions)
target_link_libraries(kivi PRIVATE kivi_parser)
target_link_libraries(kivi PRIVATE ast)
target_link_libraries(kivi PRIVATE ast_printer)

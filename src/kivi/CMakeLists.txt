add_subdirectory(util)
add_subdirectory(ast)
add_subdirectory(parser)

add_executable(kivi main.cc)

target_link_libraries(kivi PRIVATE kivi_stmts)
target_link_libraries(kivi PRIVATE kivi_expressions)
target_link_libraries(kivi PRIVATE kivi_parser)
target_link_libraries(kivi PRIVATE loguru)
target_link_libraries(kivi PRIVATE parser)
target_link_libraries(kivi PRIVATE ast)

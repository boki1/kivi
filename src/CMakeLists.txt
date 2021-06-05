add_subdirectory(extern)
add_subdirectory(utils)
add_subdirectory(frontend)
add_subdirectory(backend)
add_subdirectory(test)

################ Main

add_executable(kivi
        main.cc)

target_link_libraries(kivi PRIVATE kivi_compiler)
target_link_libraries(kivi PRIVATE kivi_ir)
target_link_libraries(kivi PRIVATE kivi_parser)
target_link_libraries(kivi PRIVATE ast_printer)
target_link_libraries(kivi PRIVATE ir_printer)
target_link_libraries(kivi PRIVATE cli)
target_link_libraries(kivi PRIVATE loguru)


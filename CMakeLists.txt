cmake_minimum_required(VERSION 3.17)
project(kivi)

set(CMAKE_CXX_STANDARD 17)

############## Global "variables"

set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(FRONTEND_DIR "${PROJECT_ROOT}/frontend")
set(PARSER_DIR "${FRONTEND_DIR}/parser")
set(GRAMMAR "${PARSER_DIR}/grammar.y")
set(LEXEMES "${PARSER_DIR}/lexemes.re")
set(BACKEND_DIR "${PROJECT_ROOT}/backend")
set(EXTERN_DIR "${PROJECT_ROOT}/extern")
set(TEST_DIR "${PROJECT_ROOT}/test")
set(UTILS_DIR "${PROJECT_ROOT}/utils")

############### Utilities

function(print)
    foreach (var ${ARGN})
        message("${var} = ${${var}}")
    endforeach ()
endfunction()

############### Testing

find_package(Catch2 CONFIG REQUIRED)
enable_testing()
include(CTest)
include(Catch)

############### Subdirectories

add_subdirectory(extern)
add_subdirectory(utils)
add_subdirectory(frontend)
add_subdirectory(backend)
add_subdirectory(test)

################ Main

add_executable(kivi
        main.cc)

target_link_libraries(kivi PRIVATE kivi_ir)
target_link_libraries(kivi PRIVATE kivi_parser)
target_link_libraries(kivi PRIVATE ast_printer)
target_link_libraries(kivi PRIVATE ir_printer)
target_link_libraries(kivi PRIVATE cli)
target_link_libraries(kivi PRIVATE loguru)

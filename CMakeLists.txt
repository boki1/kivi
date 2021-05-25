cmake_minimum_required(VERSION 3.9)
project(kivi VERSION 0.0.1
        HOMEPAGE_URL https://boki1.github.io/kivi/
        LANGUAGES C CXX
        DESCRIPTION "Simple compiler for educational purposes"
		)

add_compile_options(-g)

set(CMAKE_CXX_STANDARD 17)

############## Global "variables"

set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src")
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

enable_testing()

############### Subdirectories

add_subdirectory(src)

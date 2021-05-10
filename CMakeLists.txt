cmake_minimum_required(VERSION 3.16)

project(kivi VERSION 0.01)

add_compile_options(--std=c++17)

find_package(Catch2 CONFIG REQUIRED)
enable_testing()
include(CTest)
include(Catch)

set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_DIR "${PROJECT_ROOT}/src")
set(KIVI_SRC_DIR "${SRC_DIR}/kivi")
set(AUTOGEN_DIR "${SRC_DIR}/autogen")
set(AUTOGEN_OUTPUT_DIR "${AUTOGEN_DIR}/kivi_parser")
set(MISC_DIR "${SRC_DIR}/misc")
set(EXTERN_DIR "${SRC_DIR}/extern")

set(LEXEMES "${MISC_DIR}/lexemes.re")
set(GRAMMAR "${MISC_DIR}/grammar.y")


function(print)
    foreach (var ${ARGN})
        message("${var} = ${${var}}")
    endforeach ()
endfunction()

print(PROJECT_ROOT SRC_DIR KIVI_SRC_DIR AUTOGEN_DIR MISC_DIR EXTERN_DIR)
print(PROJECT_ROOT)

#######################

add_subdirectory(src)

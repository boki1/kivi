cmake_minimum_required(VERSION 3.17)
project(kivi_ir)

set(CMAKE_CXX_STANDARD 14)

include_directories(extern/catch2)
include_directories(extern/loguru)
include_directories(frontend/parser)

add_executable(kivi_ir
        extern/catch2/catch2.hpp
        extern/loguru/loguru.cpp
        extern/loguru/loguru.hpp
        frontend/parser/kivi_parser_error.cc
        frontend/parser/parsing_context.cc
        frontend/parser/parsing_context.hh
        frontend/parser/syntactic_structure.hh
        frontend/parser/syntax.hh
        test/frontend/ast_generation.test.cc
        test/frontend/config.test.cc
        test/frontend/example.test.cc
        test/frontend/main.test.cc
        test/frontend/parsing_context.test.cc
        main.cc)

add_subdirectory(util)

cmake_minimum_required(VERSION 3.16)
project(kivi)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(kivi
	main.cpp
	parser.cpp
	include/parser.hpp
)

cmake_minimum_required(VERSION 3.17)

project(kivi VERSION 0.01)

execute_process (
	COMMAND bash -c "make -C ${CMAKE_CURRENT_SOURCE_DIR}/src/misc all"
)

add_subdirectory(src)

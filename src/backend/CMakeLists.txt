add_subdirectory(arch)
add_subdirectory(compiler)

target_include_directories(kivi_compiler PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(x86 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
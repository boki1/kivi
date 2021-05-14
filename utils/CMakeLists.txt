add_library(
        cli
        cli/cli.cc
        cli/cli.hh
)

target_include_directories(cli PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(cli PRIVATE loguru)


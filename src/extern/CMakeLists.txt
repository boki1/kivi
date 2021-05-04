add_library(
        catch2
        catch2/catch2.hpp
)

target_include_directories(catch2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(catch2 PROPERTIES LINKER_LANGUAGE CXX)

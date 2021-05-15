# # # # #
# Catch2 - testing framework
# # # # #
add_library(
        catch2
        catch2/catch2.hpp
)

target_include_directories(catch2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(catch2 PROPERTIES LINKER_LANGUAGE CXX)

# # # # #
# Loguru - logging library
# # # # #
add_library(
        loguru
        loguru/loguru.cpp
        loguru/loguru.hpp
)

target_link_libraries(loguru PRIVATE pthread)
target_link_libraries(loguru PRIVATE dl)
set_target_properties(loguru PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(loguru PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# # # # #
# Textbox - 2D graph drawing
# # # # #
add_library(
        textbox
        textbox/textbox.hh
)

target_include_directories(textbox PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(textbox PROPERTIES LINKER_LANGUAGE CXX)

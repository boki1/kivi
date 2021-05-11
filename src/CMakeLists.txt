add_subdirectory(autogen)
add_subdirectory(extern)
add_subdirectory(kivi)

# Testing
set(BUILD_TESTING TRUE)
enable_testing()
add_subdirectory(test)
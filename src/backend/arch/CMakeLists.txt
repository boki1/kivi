add_library(arch
        all.hh)

target_link_libraries(arch PRIVATE kivi_compiler)
target_include_directories(arch PUBLIC "../${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(arch PROPERTIES LINKER_LANGUAGE CXX)

add_library(x86_64
        x86_64/x86_64_machine_target.cc
        x86_64/x86_64_machine_target.hh)

target_link_libraries(x86_64 PRIVATE kivi_compiler)
target_link_libraries(x86_64 PRIVATE arch)
target_link_libraries(x86_64 PRIVATE kivi_ir)
target_link_libraries(x86_64 PRIVATE optional_ref)
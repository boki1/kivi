add_library(kivi_compiler
        machine_target.hh
        emitter.hh
        instruction_selector.hh
        instruction_selector.cc
        liveness_analyzer.hh
        interference_graph.hh
        interference_graph.cc
        register_allocator.hh
        liveness_data.cc
        common.hh emitter.cc register_allocator.cc)

target_link_libraries(kivi_compiler PRIVATE kivi_ir)
target_link_libraries(kivi_compiler PRIVATE optional_ref)
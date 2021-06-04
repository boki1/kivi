add_library(kivi_compiler
        machine_target.hh
        emitter.hh
        instruction_selector.hh
        liveliness_analyzer.hh
        interference_graph.hh
        register_allocator.hh)

target_link_libraries(kivi_compiler PRIVATE kivi_ir)

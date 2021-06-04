#ifndef KIVI_REGISTER_ALLOCATOR_HH
#define KIVI_REGISTER_ALLOCATOR_HH

#include "interference_graph.hh"

namespace compiler
{
    class register_allocator
    {
    private:
        std::optional<interference_graph> graph;
        // TODO:
//        std::optional<std::vector<...>> excess;
    public:
        bool operator()();
        bool build_interference_graph();
//        ... spill_excess();
    };
}

#endif //KIVI_REGISTER_ALLOCATOR_HH

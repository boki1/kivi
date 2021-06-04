#ifndef KIVI_INTERFERENCE_GRAPH_HH
#define KIVI_INTERFERENCE_GRAPH_HH

#include "liveliness_analyzer.hh"
#include "register.hh"

namespace compiler
{
    class interference_graph
    {
    public:
        using colour = int;
    private:
        //TODO: registers
        liveness_analyzer m_liveness_analyzer;
        std::vector <colour> m_colours;
    public:
        void add_element();
        void build();
        std::map<register_type, colour> paint();
    };
}

#endif //KIVI_INTERFERENCE_GRAPH_HH

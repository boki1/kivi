#ifndef KIVI_EMITTER_HH
#define KIVI_EMITTER_HH

#include "machine_target.hh"
#include "instruction.hh"

namespace compiler
{
    class emitter
    {
    private:
        std::string m_output_file;
        machine_target m_strategy;
        std::vector<instruction> m_program;
    public:
        bool operator()();

        bool select_instructions();
        bool allocate_registers();
        bool prepare_runtime();
    };
}

#endif //KIVI_EMITTER_HH

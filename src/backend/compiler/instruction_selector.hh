#ifndef KIVI_INSTRUCTION_SELECTOR_HH
#define KIVI_INSTRUCTION_SELECTOR_HH

#include <ir_generation/ir_code.hh>
#include "machine_target.hh"

namespace compiler
{
    class instruction_selector
    {
    private:
        const &std::vector<intermediate_representation::tac> m_three_address_code;
         std::unordered_map<intermediate_representation::tac, machine_target::instruction> m_mapping;
         std::vector<machine_target::instruction> m_selected;

    public:
        bool operator()();
        bool select();
    };
}

#endif //KIVI_INSTRUCTION_SELECTOR_HH

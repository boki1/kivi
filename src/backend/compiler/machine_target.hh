#ifndef KIVI_MACHINE_TARGET_HH
#define KIVI_MACHINE_TARGET_HH

#include "instruction_selector.hh"
#include <ir_generation/ir_code.hh>

#include "register_allocator.hh"

namespace compiler
{
    class machine_target
    {
    public:
        class register_type
        {
        private:
            std::string m_name;
            int m_bytes;
            bool m_callee_save;
            bool m_caller_save;
        };

        class mem_address
        {
        private:
            uint16_t m_ptr;
        };

        class instruction
        {
        private:
            std::string m_name;
            unsigned m_bytes;
            unsigned m_opcode;
            std::variant<register_type, mem_address> m_operands;
        };

    private:
        std::vector<instruction> m_instruction_set;
        std::vector<register_type> m_registers;
        void (*m_stack_push_routine)();
        void (*m_stack_pop_routine)();
        instruction_selector m_instruction_selector;
        register_allocator m_register_allocator;
        std::vector<intermediate_representation::tac> m_three_address_code;

    public:
        // TODO:
//        void stack_push(value);
//        void stack_pop(value);
        const std::vector &operator()();
        const std::vector &generate();
    };
}

#endif //KIVI_MACHINE_TARGET_HH

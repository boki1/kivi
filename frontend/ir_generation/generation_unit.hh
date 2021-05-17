#ifndef KIVI_CONCRETE_CODES_HH
#define KIVI_CONCRETE_CODES_HH

#include <vector>
#include <memory>
#include <map>
#include "ir_code.hh"
#include <parser/syntax.hh>

namespace intermediate_representation {
    class generation_unit {
        /// All three address codes used in a unit to be generated
        std::vector<std::shared_ptr<tac>> m_all_tacs;

        /// Number of parameters in each function
        std::map<std::string, std::size_t> m_function_parameters;

        /// The entry point address of each function
        std::map<std::string, std::shared_ptr<tac>> m_entry_points;

        std::string m_string_constants;

    public:
        class generation_context {
            /// The number of the next register
            tac::fake_register_type m_counter;

            /// Pointer to the next instruction address
            std::shared_ptr<std::shared_ptr<tac>> m_target;

            /// Relation between AST variables and their register indexes
            std::map<std::size_t, tac::fake_register_type> m_map;

        public:
            generation_context(int counter, std::shared_ptr<std::shared_ptr<tac>> target);

            [[nodiscard]] tac::fake_register_type counter();

            [[nodiscard]] std::shared_ptr<std::shared_ptr<tac>> &target();

            [[nodiscard]] std::map<std::size_t, tac::fake_register_type> &map();

            [[nodiscard]] tac::fake_register_type increase_counter();
        };

    public:
        static std::unique_ptr<tac>
        define_tac(const std::vector<tac::fake_register_type> &operands);

        static std::unique_ptr<tac>
        define_tac(std::string ident_name, const std::vector<tac::fake_register_type> &operands);

        /*
         * The definitions of the three address code instructions and their operands
         */
        std::shared_ptr<tac> &
        define_tac(const std::unique_ptr<tac> &tac_code);

        std::shared_ptr<tac>
        tac_nop();

        std::shared_ptr<tac>
        tac_init(const std::string &ident_name, const std::vector<tac::fake_register_type> &operands);

        std::shared_ptr<tac>
        tac_add(const std::vector<tac::fake_register_type> &operands);

        std::shared_ptr<tac>
        tac_neg(const std::vector<tac::fake_register_type> &operands);

        std::shared_ptr<tac>
        tac_copy(const std::vector<tac::fake_register_type> &operands);

        std::shared_ptr<tac>
        tac_read(const std::vector<tac::fake_register_type> &operands);

        std::shared_ptr<tac>
        tac_write(const std::vector<tac::fake_register_type> &operands);

        std::shared_ptr<tac>
        tac_eq(const std::vector<tac::fake_register_type> &operands);

        std::shared_ptr<tac>
        tac_ifnz(const std::vector<tac::fake_register_type> &operands);

        std::shared_ptr<tac>
        tac_fcall(const std::vector<tac::fake_register_type> &operands);

        std::shared_ptr<tac>
        tac_rtrn(const std::vector<tac::fake_register_type> &operands);

        tac::fake_register_type
        generate_ir(const syntax_analyzer::expression &code, generation_context &ctx);

        void
        generate_function(const syntax_analyzer::function &function);

        void
        generate(const std::vector<syntax_analyzer::function> &ctx_functions);

    public:
        [[nodiscard]] std::vector<std::shared_ptr<tac>> & all_tacs();

        [[nodiscard]] std::map<std::string, std::size_t> & function_parameters();

        [[nodiscard]] std::map<std::string, std::shared_ptr<tac>> & entry_points();

        [[nodiscard]] std::string & string_constants();

    };
}
#endif //KIVI_CONCRETE_CODES_HH

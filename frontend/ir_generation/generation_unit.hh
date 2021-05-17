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

        class generation_context {
            /// The number of the next register
            tac::fake_register_type counter;

            /// Pointer to the next instruction address
            std::shared_ptr<std::shared_ptr<tac>> target;

            /// Relation between AST variables and their register indexes
            std::map<std::size_t, tac::fake_register_type> map;
        };

        tac::fake_register_type generate(const syntax_analyzer::expression &code, generation_context &ctx);

    public:
        static std::unique_ptr<tac> define_tac(std::vector<tac::fake_register_type> &operands);

        std::shared_ptr<tac> &define_tac(std::unique_ptr<tac> &tac_code);

        void generate_function(syntax_analyzer::function &fun);

    public:
        [[nodiscard]] const std::vector<std::shared_ptr<tac>> &all_tacs() const;

        [[nodiscard]] const std::map<std::string, std::size_t> &function_parameters() const;

        [[nodiscard]] const std::map<std::string, std::shared_ptr<tac>> &entry_points() const;

        [[nodiscard]] const std::string &string_constants() const;


    };
}
#endif //KIVI_CONCRETE_CODES_HH

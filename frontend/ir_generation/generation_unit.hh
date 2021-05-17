#ifndef KIVI_CONCRETE_CODES_HH
#define KIVI_CONCRETE_CODES_HH

#include <vector>
#include <memory>
#include <map>
#include "ir_code.hh"

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
        static std::unique_ptr<tac> &define_tac(std::vector<tac::fake_register_type> &operands);

        std::shared_ptr<tac> &define_tac(std::unique_ptr<tac> &tac_code);

    public:
        [[nodiscard]] const std::vector<std::shared_ptr<tac>> &all_tacs() const;

        [[nodiscard]] const std::map<std::string, std::size_t> &function_parameters() const;

        [[nodiscard]] const std::map<std::string, std::shared_ptr<tac>> &entry_points() const;

        [[nodiscard]] const std::string &string_constants() const;
    };
}
#endif //KIVI_CONCRETE_CODES_HH

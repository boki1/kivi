#include "generation_unit.hh"

namespace intermediate_representation {
    std::unique_ptr <tac> &intermediate_representation::generation_unit::define_tac(std::vector<tac::fake_register_type> &operands) {
        std::unique_ptr<tac> result = std::make_unique<tac>(std::move(tac{operands}));
        return result;
    }

    std::shared_ptr<tac> &generation_unit::define_tac(std::unique_ptr<tac> &tac_code) {
        m_all_tacs.emplace_back(std::make_shared<tac>(*tac_code));
        return m_all_tacs.back();
    }

    const std::vector<std::shared_ptr<tac>> &generation_unit::all_tacs() const {
        return m_all_tacs;
    }

    const std::map<std::string, std::size_t> &generation_unit::function_parameters() const {
        return m_function_parameters;
    }

    const std::map<std::string, std::shared_ptr<tac>> &generation_unit::entry_points() const {
        return m_entry_points;
    }

    const std::string &generation_unit::string_constants() const {
        return m_string_constants;
    }

}

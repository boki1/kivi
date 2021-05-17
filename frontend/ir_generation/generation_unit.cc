#include "generation_unit.hh"
#include <utility>
#include <variant>
#include <memory>

namespace sa = syntax_analyzer;

namespace intermediate_representation {
    std::unique_ptr<tac>
    intermediate_representation::generation_unit::define_tac(
            const std::vector<tac::fake_register_type> &operands) {
        return std::make_unique<tac>(tac{operands});
    }

    std::shared_ptr<tac> &
    generation_unit::define_tac(const std::unique_ptr<tac> &tac_code) {
        return m_all_tacs.emplace_back(std::make_shared<tac>(*tac_code));
    }

    std::shared_ptr<tac>
    generation_unit::tac_nop(const std::vector<tac::fake_register_type> &operands) {
        return define_tac(std::make_unique<tac>(tac{tac::tac_type::Nop, operands}));
    }

    std::shared_ptr<tac>
    generation_unit::tac_init(const std::string &ident_name, const std::vector<tac::fake_register_type> &operands) {
        return define_tac(operands);
    }

    std::shared_ptr<tac>
    generation_unit::tac_add(const std::vector<tac::fake_register_type> &operands) {
        return define_tac(std::make_unique<tac>(tac{tac::tac_type::Add, operands}));
    }

    std::shared_ptr<tac>
    generation_unit::tac_neg(const std::vector<tac::fake_register_type> &operands) {
        return define_tac(std::make_unique<tac>(tac{tac::tac_type::Negate, operands}));
    }

    std::shared_ptr<tac>
    generation_unit::tac_copy(const std::vector<tac::fake_register_type> &operands) {
        return define_tac(std::make_unique<tac>(tac{tac::tac_type::Copy, operands}));
    }

    std::shared_ptr<tac>
    generation_unit::tac_read(const std::vector<tac::fake_register_type> &operands) {
        return define_tac(std::make_unique<tac>(tac{tac::tac_type::Read, operands}));
    }

    std::shared_ptr<tac>
    generation_unit::tac_write(const std::vector<tac::fake_register_type> &operands) {
        return define_tac(std::make_unique<tac>(tac{tac::tac_type::Write, operands}));
    }

    std::shared_ptr<tac>
    generation_unit::tac_eq(const std::vector<tac::fake_register_type> &operands) {
        return define_tac(std::make_unique<tac>(tac{tac::tac_type::Equals, operands}));
    }

    std::shared_ptr<tac>
    generation_unit::tac_ifnz(const std::vector<tac::fake_register_type> &operands) {
        return define_tac(operands);
    }

    std::shared_ptr<tac>
    generation_unit::tac_fcall(const std::vector<tac::fake_register_type> &operands) {
        return define_tac(std::make_unique<tac>(tac{tac::tac_type::FunctionCall, operands}));
    }

    std::shared_ptr<tac>
    generation_unit::tac_rtrn(const std::vector<tac::fake_register_type> &operands) {
        return define_tac(std::make_unique<tac>(tac{tac::tac_type::Return, operands}));
    }

    static auto
    put(std::shared_ptr<tac> tac_code, const generation_unit::generation_context &ctx) {
        for (*ctx.target() = tac_code; tac_code; tac_code = *ctx.target())
            *ctx.target() = tac_code->next();
    }

//    tac::fake_register_type
//    generation_unit::generate_ir(const sa::expression &code, generation_context &ctx) {
//        auto result = ~tac::fake_register_type{};
//
//        switch (code.get_type()) {
//            case sa::expression::type::Identifier:
//                const auto &ident = std::get<sa::identifier>(code.terminal());
//                switch (ident.get_type()) {
//                    case sa::identifier::type::Function:
//                        result = ctx.increase_counter();
//                        put(tac_init({result, ident.name(), 0l}), &ctx);
//                        break;
//                    case sa::identifier::type::Local:
//                    case sa::identifier::type::Parameter:
//                    case sa::identifier::type::Undefined:
//                }
//        }
//    }

    const std::vector<std::shared_ptr<tac>> &
    generation_unit::all_tacs() const {
        return m_all_tacs;
    }

    const std::map<std::string, std::size_t> &
    generation_unit::function_parameters() const {
        return m_function_parameters;
    }

    const std::map<std::string, std::shared_ptr<tac>> &
    generation_unit::entry_points() const {
        return m_entry_points;
    }

    const std::string &
    generation_unit::string_constants() const {
        return m_string_constants;
    }

    tac::fake_register_type
    generation_unit::generation_context::counter() const {
        return m_counter;
    }

    const std::shared_ptr<std::shared_ptr<tac>> &
    generation_unit::generation_context::target() const {
        return m_target;
    }

    const std::map<std::size_t, tac::fake_register_type> &
    generation_unit::generation_context::map() const {
        return m_map;
    }

    tac::fake_register_type
    generation_unit::generation_context::increase_counter() {
        return m_counter++;
    }
}

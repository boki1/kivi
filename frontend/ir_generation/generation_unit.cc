#include "generation_unit.hh"
#include <utility>
#include <variant>
#include <memory>
#include <iostream>
#include <transform_iterator/transform_iterator.hh>

namespace sa = syntax_analyzer;

namespace intermediate_representation {
    std::unique_ptr<tac>
    intermediate_representation::generation_unit::define_tac(const std::vector<tac::fake_register_type> &operands) {
        return std::make_unique<tac>(tac{operands});
    }

    std::unique_ptr<tac>
    intermediate_representation::generation_unit::define_tac(const std::string ident_name,
                                                             const std::vector<tac::fake_register_type> &operands) {
        return std::make_unique<tac>(tac{operands});
    }

    std::shared_ptr<tac> &
    generation_unit::define_tac(const std::unique_ptr<tac> &tac_code) {
        return m_all_tacs.emplace_back(std::make_shared<tac>(*tac_code));
    }

    std::shared_ptr<tac>
    generation_unit::tac_nop() {
        return define_tac(std::make_unique<tac>(tac{tac::tac_type::Nop, {}}));
    }

    std::shared_ptr<tac>
    generation_unit::tac_init(const std::string &ident_name, const std::vector<tac::fake_register_type> &operands) {
        return define_tac(ident_name, operands);
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
    put(std::shared_ptr<tac> tac_code, generation_unit::generation_context &ctx) {
        for (*ctx.target() = tac_code; tac_code; tac_code = *ctx.target())
            *ctx.target() = tac_code->next();
    }

    tac::fake_register_type
    generation_unit::generate_ir(const sa::expression &code, generation_context &ctx) {
        auto result = ~tac::fake_register_type{};

        switch (code.get_type()) {
            case sa::expression::type::Identifier: {
                const auto &ident = std::get<sa::identifier>(code.terminal());
                switch (ident.get_type()) {
                    case sa::identifier::type::Function: {
                        result = ctx.increase_counter();
                        put(tac_init(ident.name(), {result, 0l}), ctx);
                        break;
                    }
                    case sa::identifier::type::Local: {
                        result = ctx.map().emplace(ident.index(), ctx.increase_counter()).first->second;
                        break;
                    }
                    case sa::identifier::type::Parameter: {
                        result = ident.index();
                        break;
                    }
                    case sa::identifier::type::Undefined: {
                        std::cerr << "Undefined identifier\n";
                        break;
                    }
                }
            }
            case syntax_analyzer::expression::type::Negation: {
                result = ctx.increase_counter();
                std::vector<tac::fake_register_type> operands = {result, generate_ir(code.operands().front(), ctx)};
                put(tac_neg(operands), ctx);
                break;
            }
            case syntax_analyzer::expression::type::Return: {
                result = generate_ir(code.operands().front(), ctx);
                put(tac_rtrn({result}), ctx);
                break;
            }
            case syntax_analyzer::expression::type::Number: {
                result = ctx.increase_counter();
                put(tac_init("", {result, std::get<int>(code.terminal())}), ctx);
                break;
            }
            case syntax_analyzer::expression::type::Nop: {
                result = ctx.increase_counter();
                put(tac_init("", {result, 0L}), ctx);
                break;
            }
            case syntax_analyzer::expression::type::Addition:
            case syntax_analyzer::expression::type::Equality:
            case syntax_analyzer::expression::type::Sequence: {
                for (auto &i : code.operands()) {
                    tac::fake_register_type prev = result;
                    tac::fake_register_type last = result = generate_ir(i, ctx);
                    if (prev != ~0u) {
                        result = ctx.increase_counter();
                        if (code.get_type() == sa::expression::type::Addition) {
                            put(tac_add({result, prev, last}), ctx);
                        } else if (code.get_type() == sa::expression::type::Equality) {
                            put(tac_eq({result, prev, last}), ctx);
                        }
                    }
                }
                break;
            }
            case syntax_analyzer::expression::type::While:
            case syntax_analyzer::expression::type::If: {
                result = ctx.increase_counter();
                /// This is an If() statement. Therefore three mandatory statements are created:
                // TODO: unique?
                std::shared_ptr<tac> b_then = tac_init("", {result, 1l});        // Then-branch
                std::shared_ptr<tac> b_else = tac_init("", {result, 0l});        // Else-branch
                std::shared_ptr<tac> end = tac_nop();
                b_then->next() = b_else->next() = end; // A common target for both.

                /// For loops reference to the first expression is needed.
                /// @note A reference to the pointer is needed instead of copy since it'll change onwards.
                std::shared_ptr<tac> &begin = *ctx.target();
                for (const auto &i : code.operands()) {
                    /// Get IR.
                    tac::fake_register_type i_ir = generate_ir(i, ctx);
                    // Don't create a branch after contingent statements in a loop.
                    if (code.get_type() == sa::expression::type::While && i != code.operands().front()) {
                        continue;
                    }
                    // Immediately after the expression, create a branch on its result.
                    std::shared_ptr<tac> condition = *ctx.target() = tac_ifnz({i_ir, 0});

                    *ctx.target() = condition->next();
                    condition->condition() = b_else;
                }
                // The end of the statement chain is linked into b_then.
                // For loops, the chain is linked back into the start of the loop instead.
                *ctx.target() = code.get_type() == sa::expression::type::While ? begin : b_then;
                *ctx.target() = end->next();  // Code continues after the end node.
                break;
            }
            case syntax_analyzer::expression::type::Copy: {
                const auto &src = code.operands().front();
                const auto &dest = code.operands().back();
                auto temp = generate_ir(src, ctx);
                result = generate_ir(dest, ctx);
                put(tac_copy({result, temp}), ctx);
                break;
            }
            case syntax_analyzer::expression::type::Multiplication: {
                break;
            }
            case syntax_analyzer::expression::type::Division: {
                break;
            }
            case syntax_analyzer::expression::type::ModularDivision: {
                break;
            }
            case syntax_analyzer::expression::type::FunctionCall: {
                result = ctx.increase_counter();

                std::vector<tac::fake_register_type> operands = {result,
                                                                 *make_transform_iterator(code.operands().begin(),
                                                                                          code.operands().end(),
                                                                                          [&](const sa::expression &p) {
                                                                                              return generate_ir(p,
                                                                                                                 ctx);
                                                                                          }),
                                                                 *transform_iterator<tac::fake_register_type>{}};

                put(tac_fcall(operands), ctx);
                break;
            }
            /// Strings are not supported yet.
            case syntax_analyzer::expression::type::String:
                break;
        }
        return result;
    }

    void
    generation_unit::generate_function(const syntax_analyzer::function &function) {
        function_parameters()[function.name()] = function.parameters();

        generation_context ctx{function.parameters(), std::make_shared<std::shared_ptr<tac>>(entry_points()[function.name()])};
        generate_ir(function.body(), ctx);
    }

    void
    generation_unit::generate(const std::vector<sa::function> &ctx_functions) {
        for (const auto &f: ctx_functions) {
            generate_function(f);
        }
    }

    std::vector<std::shared_ptr<tac>> &
    generation_unit::all_tacs() {
        return m_all_tacs;
    }

    std::map<std::string, std::size_t> &
    generation_unit::function_parameters() {
        return m_function_parameters;
    }

    std::map<std::string, std::shared_ptr<tac>> &
    generation_unit::entry_points() {
        return m_entry_points;
    }

    std::string &
    generation_unit::string_constants() {
        return m_string_constants;
    }

    generation_unit::generation_context::generation_context(int counter, std::shared_ptr<std::shared_ptr<tac>> target)
            : m_counter(counter), m_target(std::move(target)), m_map({}) {}

    tac::fake_register_type
    generation_unit::generation_context::counter() {
        return m_counter;
    }

    std::shared_ptr<std::shared_ptr<tac>> &
    generation_unit::generation_context::target() {
        return m_target;
    }

    std::map<std::size_t, tac::fake_register_type> &
    generation_unit::generation_context::map() {
        return m_map;
    }

    tac::fake_register_type
    generation_unit::generation_context::increase_counter() {
        return m_counter++;
    }
}

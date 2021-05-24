#include <iostream>
#include <transform_iterator/transform_iterator.hh>
#include <algorithm>

#include "generation_context.hh"
#include "generation_unit.hh"

namespace sa = syntax_analyzer;
using sa_type = sa::expression::type;
namespace ir = intermediate_representation;
using gu = ir::generation_unit;

namespace intermediate_representation {
//!
//! Common functions for modifying the tacs chain
//!

/**
 * @brief Places a chain of TAC
 * @param code The "head" of the TAC chain
 * @param ctx The generation context
 */
    static void place_chain(tac::tac_ptr code,
                            generation_unit::generation_context &ctx) {
        for (*ctx.target() = code; code; code = *ctx.target())
            ctx.set_target(code->next_double_ptr());
    }

/**
 * @brief Creates a new virtual register
 * @param ctx The generation context
 * @return The new virtual register
 */
    static tac::vregister_type make_vreg(gu::generation_context &ctx) {
        auto vreg = ctx.increase_counter();
        return vreg;
    }

//!
//!	Concrete generators
//!

    void gu::generate_identifier(const syntax_analyzer::expression &e,
                                 generation_context &gtx) {
        /// We don't have to look out for exception thrown by std::get<> since we are
        /// _sure_ that there is an identifier in the variant
        const auto &ident = std::get<sa::identifier>(e.terminal());

        switch (ident.get_type()) {
            case sa::identifier::type::Function: {
                auto vreg = make_vreg(gtx);
                (void) gtx.update_temp(vreg);
                auto code = tac_init(0u, ident.name(), gtx.fetch_temp());
                place_chain(code, gtx);
                break;
            }
            case sa::identifier::type::Local: {
                auto pair_ = gtx.map_mut().emplace(ident.index(), gtx.increase_counter());
                gtx.update_temp(pair_.first->second);
                break;
            }
            case sa::identifier::type::Parameter: {
                gtx.update_temp(ident.index());
                break;
            }
            case sa::identifier::type::Undefined: {
                std::cerr << "Err: During identifier translation to IR!\n";
                return;
            }
        }
    }

    void gu::generate_negation(const syntax_analyzer::expression &expr,
                               generation_context &gtx) {
        gtx.update_temp(make_vreg(gtx));
        auto vreg = generate_ir(expr.operands().front(), gtx);
        tac::operands_type operands = {gtx.fetch_temp(), vreg};
        auto code = tac_neg(operands);
        place_chain(code, gtx);
    }

    void gu::generate_return(const syntax_analyzer::expression &expr,
                             generation_context &gtx) {
        auto vreg = generate_ir(expr.operands().front(), gtx);
        gtx.update_temp(vreg);
        auto code = tac_return({gtx.fetch_temp()});
        place_chain(code, gtx);
    }

    void gu::generate_number(const syntax_analyzer::expression &e,
                             generation_context &gtx) {
        gtx.update_temp(make_vreg(gtx));
        auto num = static_cast<unsigned int>(std::get<int>(e.terminal()));
        auto code = tac_init(num, "", gtx.fetch_temp());
        place_chain(code, gtx);
    }

    void gu::generate_nop(const syntax_analyzer::expression &e,
                          generation_context &gtx) {
        gtx.update_temp(make_vreg(gtx));
        auto code = tac_init(0u, "", gtx.fetch_temp());
        place_chain(code, gtx);
    }

    void gu::generate_sequence(const syntax_analyzer::expression &e, generation_context &gtx) {
        for (auto &i : e.operands()) {
            tac::vregister_type prev = gtx.pop_temp();
            tac::vregister_type last = generate_ir(i, gtx);
            gtx.push_temp(last);

            if (prev == ~0u)
                continue;

            if (e.get_type() == sa::expression::type::Addition) {
                auto vreg = make_vreg(gtx);
                gtx.push_temp(vreg);
                auto code = tac_add({vreg, prev, last});
                place_chain(code, gtx);
            } else if (e.get_type() == sa::expression::type::Equality) {
                auto vreg = make_vreg(gtx);
                gtx.push_temp(vreg);
                auto code = tac_eq({vreg, prev, last});
                place_chain(code, gtx);
            } else if (e.get_type() == sa::expression::type::Multiplication) {
                int a_num = std::get<int>(e.operands().at(0).terminal());
                int b_num = std::get<int>(e.operands().at(1).terminal());

                // The following two vars are used in case of multiplication with zero
                int non_zero_operand = (a_num > 0) ? a_num : b_num;
                auto potentially_zero_reg = (a_num > 0) ? last : prev;

                auto tmp_sum_res_reg = make_vreg(gtx);
                gtx.push_temp(tmp_sum_res_reg);

                place_chain(tac_copy({tmp_sum_res_reg, potentially_zero_reg}), gtx);

                auto sum_reg = make_vreg(gtx);
                gtx.push_temp(sum_reg);

                for (int j = 0; j < non_zero_operand - 1; ++j) {
                    auto code = tac_add({sum_reg, tmp_sum_res_reg, potentially_zero_reg});
                    place_chain(code, gtx);

                    place_chain(tac_copy({tmp_sum_res_reg, sum_reg}), gtx);
                }
            } else {
                gtx.update_temp(last);
            }
        }
    }

    void gu::generate_conditional(const syntax_analyzer::expression &expr, generation_context &gtx) {
        gtx.update_temp(make_vreg(gtx));

        /// This is either an `if()` or a `while()` statement. Therefore three
        /// mandatory statements are created:
        tac *then_body = tac_init(1u, "", gtx.fetch_temp());
        tac *else_body = tac_init(0u, "", gtx.fetch_temp());

        tac *end = tac_nop();
        then_body->next_mut() = end;
        else_body->next_mut() = end;

        /// For loops reference to the first expression is required.
        /// @note Reference to the pointer is needed instead of copy since it'll
        /// change onwards.
        tac *&loop_begin = *gtx.target();

        for (const auto &operand : expr.operands()) {
            tac::vregister_type vreg = generate_ir(operand, gtx);

            if (expr.get_type() == sa_type::While && operand != expr.operands().front())
                continue;

            // Immediately after the expression, create a branch on its result.
            *gtx.target() = tac_ifnz({vreg});
            tac *if_stmt = *gtx.target();

            // Setup this chain: target -> if_stmt.condition -> else_body
            auto temp1 = if_stmt->condition_double_ptr();
            gtx.set_target(temp1);
            if_stmt->next_mut() = else_body;
        }

        // The end of the statement chain is linked into then_body.
        // For loops, the chain is linked back into the start of the loop instead.

        if (expr.get_type() == sa_type::While)
            *gtx.target() = loop_begin;
        else
            *gtx.target() = then_body;

        (void) gtx.pop_temp();
        gtx.set_target(end->next_double_ptr());
    }

    void gu::generate_copy(const syntax_analyzer::expression &e,
                           generation_context &gtx) {
        const auto &src = e.operands().front();
        const auto &dest = e.operands().back();
        auto temp = generate_ir(src, gtx);
        gtx.update_temp(generate_ir(dest, gtx));
        place_chain(tac_copy({gtx.fetch_temp(), temp}), gtx);
    }

    void gu::generate_funcall(const syntax_analyzer::expression &expr, generation_context &gtx) {
        gtx.update_temp(gtx.increase_counter());

        std::vector<tac::vregister_type> vreg_parameters;
        vreg_parameters.reserve(expr.operands().size());

        std::transform(expr.operands().begin(), expr.operands().end(), std::back_inserter(vreg_parameters),
                       [&](const sa::expression &operand) {
                           return generate_ir(operand, gtx);
                       });

        // Insert the return virtual register
        vreg_parameters.insert(vreg_parameters.begin(), gtx.fetch_temp());

        place_chain(tac_fcall(vreg_parameters), gtx);
    }
} // namespace intermediate_representation
#include <iostream>
#include <transform_iterator/transform_iterator.hh>

#include "generation_context.hh"
#include "generation_unit.hh"

namespace sa = syntax_analyzer;
namespace ir = intermediate_representation;
using gu = ir::generation_unit;

namespace intermediate_representation
{
	//!
	//! Common functions for modifying the tacs chain
	//!

	/**
	 * @brief Places a chain of TAC
	 * @param code The "head" of the TAC chain
	 * @param ctx The generation context
	 */
	static void
	place_chain(tac::tac_ptr code, const generation_unit::generation_context& ctx)
	{
		for (*ctx.target() = code; code; code = *ctx.target())
			*ctx.target() = code->next();
	}

	/**
	 * @brief Creates a new virtual register
	 * @param ctx The generation context
	 * @return The new virtual register
	 */
	static tac::vregister_type
	make_vreg(gu::generation_context& ctx, bool store_it = false)
	{
		auto vreg = ctx.increase_counter();
		if (store_it)
			return ctx.store_vreg(vreg);
		return vreg;
	}

	//!
	//!	Concrete generators
	//!
	void gu::generate_identifier(const syntax_analyzer::expression& e, generation_context& gtx)
	{
		/// We don't have to look out for exception thrown by std::get<> since we are _sure_ that there
		/// is an identifier in the variant
		const auto& ident = std::get<sa::identifier>(e.terminal());

		switch (ident.get_type())
		{
		case sa::identifier::type::Function:
		{
			place_chain(tac_init(make_vreg(gtx), ident.name(), 0l), gtx);
			break;
		}
		case sa::identifier::type::Local:
		{
			gtx.store_vreg(gtx.map_mut().emplace(ident.index(), gtx.increase_counter()).first->second);
			break;
		}
		case sa::identifier::type::Parameter:
		{
			gtx.store_vreg(ident.index());
			break;
		}
		case sa::identifier::type::Undefined:
		{
			std::cerr << "Err: During identifier translation to IR!\n";
			return;
		}

		}
	}

	void gu::generate_negation(const syntax_analyzer::expression& e, generation_context& gtx)
	{
		gtx.store_vreg(gtx.increase_counter());
		tac::operands_type operands = { gtx.load_vreg(), generate_ir(e.operands().front(), gtx) };
		place_chain(tac_neg(operands), gtx);
	}

	void gu::generate_return(const syntax_analyzer::expression& e, generation_context& gtx)
	{
		gtx.store_vreg(generate_ir(e.operands().front(), gtx));
		place_chain(tac_return({ gtx.load_vreg() }), gtx);
	}

	void gu::generate_number(const syntax_analyzer::expression& e, generation_context& gtx)
	{
		gtx.store_vreg(gtx.increase_counter());
		auto num = static_cast<unsigned>(std::get<int>(e.terminal()));
		place_chain(tac_init(gtx.load_vreg(), "", num), gtx);
	}

	void gu::generate_nop(const syntax_analyzer::expression& e, generation_context& gtx)
	{
		gtx.store_vreg(gtx.increase_counter());
		place_chain(tac_init(gtx.load_vreg(), "", 0u), gtx);
	}

	void gu::generate_sequence(const syntax_analyzer::expression& e, generation_context& gtx)
	{
		for (auto& i : e.operands())
		{
			tac::vregister_type prev = gtx.load_vreg();
			tac::vregister_type last = generate_ir(i, gtx);
			gtx.store_vreg(last);

			if (prev == -1)
			{
				continue;
			}

			gtx.store_vreg(gtx.increase_counter());
			if (e.get_type() == sa::expression::type::Addition)
			{
				place_chain(tac_add({ gtx.load_vreg(), prev, last }), gtx);
			}
			else if (e.get_type() == sa::expression::type::Equality)
			{
				place_chain(tac_eq({ gtx.load_vreg(), prev, last }), gtx);
			}
		}
	}

	void gu::generate_conditional(const syntax_analyzer::expression& e, generation_context& gtx)
	{
		gtx.store_vreg(gtx.increase_counter());
		/// This is an If() statement. Therefore three mandatory statements are created:

		tac* b_then = tac_init(1u, "", gtx.load_vreg());        // Then-branch
		tac* b_else = tac_init(0u, "", gtx.load_vreg());        // Else-branch
		tac* end = tac_nop();
		b_then->next_mut() = b_else->next_mut() = end; // A common target for both.

		/// For loops reference to the first expression is needed.
		/// @note A reference t	o the pointer is needed instead of copy since it'll change onwards.
		tac*& begin = *gtx.target();
		for (const auto& i : e.operands())
		{
			/// Get IR.
			tac::vregister_type i_ir = generate_ir(i, gtx);
			// Don't create a branch after contingent statements in a loop.
			if (e.get_type() == sa::expression::type::While && i != e.operands().front())
			{
				continue;
			}
			// Immediately after the expression, create a branch on its result.
			tac* condition = *gtx.target() = tac_ifnz({ i_ir, 0 });

			*gtx.target() = condition->next();
			condition->condition_mut() = b_else;
		}
		// The end of the statement chain is linked into b_then.
		// For loops, the chain is linked back into the start of the loop instead.
		*gtx.target() = e.get_type() == sa::expression::type::While ? begin : b_then;
		*gtx.target() = end->next();  // Code continues after the end node.
	}

	void gu::generate_copy(const syntax_analyzer::expression& e, generation_context& gtx)
	{
		const auto& src = e.operands().front();
		const auto& dest = e.operands().back();
		auto temp = generate_ir(src, gtx);
		gtx.store_vreg(generate_ir(dest, gtx));
		place_chain(tac_copy({ gtx.load_vreg(), temp }), gtx);
	}

	void gu::generate_funcall(const syntax_analyzer::expression& e, generation_context& gtx)
	{
		gtx.store_vreg(gtx.increase_counter());

		std::vector<tac::vregister_type> operands = {
			gtx.load_vreg(),
			*make_transform_iterator(
				e.operands().begin(),
				e.operands().end(),
				[&](const sa::expression& p)
				{
				  return generate_ir(p, gtx);
				}),
			*transform_iterator<tac::vregister_type>{}
		};

		place_chain(tac_fcall(operands), gtx);
	}
}
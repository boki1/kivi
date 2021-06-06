#include <memory>
#include <iostream>
#include <list>
#include <map>

#include "generation_unit.hh"
#include "generation_context.hh"

namespace sa = syntax_analyzer;

namespace intermediate_representation
{
	/// Defines an already constructed TAC
	tac*
	generation_unit::define_tac(const tac& code)
	{
		m_tacs.emplace_back(std::make_unique<tac>(code));
		return m_tacs.back().get();
	}

	tac::vregister_type
	generation_unit::generate_ir(const sa::expression& code, generation_context& ctx)
	{
		ctx.push_temp(~0u);

		using expr_type = sa::expression::type;

		/// Each AST expression gets translated to IR according to its type -- hence `expr_type`
		switch (code.get_type())
		{
		case expr_type::Identifier:
		{
			generate_identifier(code, ctx);
			break;
		}
		case expr_type::Negation:
		{
			generate_negation(code, ctx);
			break;
		}
		case expr_type::Return:
		{
			generate_return(code, ctx);
			break;
		}
		case expr_type::Number:
		{
			generate_number(code, ctx);
			break;
		}
		case expr_type::Nop:
		{
			generate_nop(code, ctx);
			break;
		}

		case expr_type::Addition:
		case expr_type::Equality:
		case expr_type::Sequence:
		case expr_type::Multiplication:
		case expr_type::ModularDivision:
		case expr_type::Division:
		{
			// TODO:
			// Simplify multiplication, division, modular division into a set of additions
			generate_sequence(code, ctx);
			break;
		}
		case expr_type::While:
		case expr_type::If:
		{
			generate_conditional(code, ctx);
			break;
		}
		case expr_type::Copy:
		{
			generate_copy(code, ctx);
			break;
		}
		case expr_type::FunctionCall:
		{
			generate_funcall(code, ctx);
			break;
		}
		case expr_type::String:
			/* Do nothing */
			/* String are not supported yet */
			break;
		}

		return ctx.pop_temp();
	}

	generation_unit::generation_context generation_unit::prepare_context(const syntax_analyzer::function& function)
	{
		// Add function and parameter list size relation
		function_parameters_mut()[function.name()] = function.parameters();

		// Add an entry in for the function (initially the first TAC is at `nullptr`)
		tac** target_ptr = &(entry_points_mut()[function.name()] = nullptr);

		return generation_unit::generation_context{ static_cast<unsigned int>(function.parameters()), target_ptr };
	}

	void
	generation_unit::generate_function(const syntax_analyzer::function& function)
	{
		auto ctx = prepare_context(function);
		generate_ir(function.body(), ctx);
	}

	void
	generation_unit::generate(const std::vector<sa::function>& ctx_functions)
	{
		for (const auto& f: ctx_functions)
		{
			generate_function(f);
		}
	}

	void
	generation_unit::labelize()
	{
		struct lineinfo
		{
			std::string label;
			bool is_done = false;
			bool is_referenced = false;
		};

		std::map<tac*, lineinfo> source_index{};
		std::list<tac*> remaining_codes{};

		auto add_label = [l = 0lu](lineinfo& d) mutable
		{
		  d.label = ('L' + std::to_string(l++));
		};

		for (const auto& entry_point : entry_points())
		{
			remaining_codes.push_back(entry_point.second);
			source_index[entry_point.second].label = entry_point.first;
		}

		for (const auto& tac: tacs())
		{
			if (tac->next())
			{
				auto& code_idx = source_index[tac->next()];

				if (code_idx.label.empty() && code_idx.is_referenced)
					add_label(code_idx);

				code_idx.is_referenced = true;
			}

			if (tac->condition().has_value())
			{
				auto& code_idx = source_index[tac->condition().value()];

				if (code_idx.label.empty())
					add_label(code_idx);
			}
		}

		while (!remaining_codes.empty())
		{
			tac * code_chain = remaining_codes.front();
			remaining_codes.pop_front();

			bool jmp = false;

			while (code_chain)
			{
				auto& code_idx = source_index[code_chain];

				if (code_idx.is_done)
				{
					if (jmp)
						code_chain->place_branching_label(code_idx.label);
					break;
				}

				code_idx.is_done = true;

				if (!code_idx.label.empty())
					code_chain->labelize(code_idx.label);



				if (code_chain->condition().has_value())
				{
					auto& branch_stats = source_index.at(code_chain->condition().value());
					code_chain->place_branching_label(branch_stats.label);
					if (!branch_stats.is_done)
						remaining_codes.push_front(code_chain->condition().value());
				}

				code_chain = code_chain->next();
				jmp = true;
			}

		}
	}

}
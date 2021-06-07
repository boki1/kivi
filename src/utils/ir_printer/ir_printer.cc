#include <iostream>
#include <list>

#include <ir_generation/ir_code.hh>

#include "ir_printer.hh"

namespace ir = intermediate_representation;
using ir_type = ir::tac::type;

namespace printer
{
	// Colourful constants
	const std::string PURPLE_COLOR = "\033[1;35m ";
	const std::string GREEN_COLOR = "\033[1;32m ";
	const std::string CYAN_COLOR = "\033[1;36m";
	const std::string WHITE_COLOR = "\033[1;37m";

	void print_ir(const ir::tac& tac_code, std::ostream& os)
	{
		os << "  " << PURPLE_COLOR;
		switch (tac_code.get_type())
		{
		case ir_type::Nop:
			os << "nop";
			break;
		case ir_type::Init:
			os << "init";
			break;
		case ir_type::Add:
			os << "add";
			break;
		case ir::tac::type::Negate:
			os << "neg";
			break;
		case ir_type::Copy:
			os << "copy";
			break;
		case ir_type::Multiplication:
			os << "mult";
			break;
		case ir_type::Division:
			os << "div";
			break;
		case ir_type::Modulo:
			os << "mod";
			break;
		case ir_type::Equals:
			os << "eq";
			break;
		case ir_type::IfNotZero:
			os << "ifnz";
			break;
		case ir_type::FunctionCall:
			os << "call";
			break;
		case ir_type::Return:
			os << "ret";
			break;
		case ir_type::Goto:
			os << "goto\t" << WHITE_COLOR << tac_code.branching_label();
			break;
		}

		os << "\t" << WHITE_COLOR;

		for (const auto& vreg: tac_code.operands())
			os << " R" << vreg;

		// Additional output

		switch (tac_code.get_type())
		{
		case ir::tac::type::Init:
			if (tac_code.identifier().empty())
				os << " #" << tac_code.value();
			else
				os << " \"" << tac_code.identifier() << "\"";
			break;
		default:;
			/* nothing */
		}
	}

	void print_ir(intermediate_representation::generation_unit& gunit, std::ostream& os)
	{
		std::unordered_map<ir::tac*, bool> performed;
		std::list<ir::tac*> remaining_codes;

		std::transform(gunit.entry_points().begin(), gunit.entry_points().end(), std::back_inserter(remaining_codes), [&performed](const auto& entry)
		{
		  performed.insert(std::make_pair(entry.second, false));
		  return entry.second;
		});

		for (const auto& TAC: gunit.tacs())
		{
			if (TAC->next())
				performed.insert_or_assign(TAC->next(), false);
			if (TAC->condition().has_value())
				performed.insert_or_assign(TAC->condition_ptr(), false);
		}

		while (!remaining_codes.empty())
		{
			ir::tac* code_chain = remaining_codes.front();
			remaining_codes.pop_front();

			bool jmp = false;
			while (code_chain)
			{
				auto& index = performed[code_chain];
				if (index)
				{
					if (jmp)
						os << PURPLE_COLOR << "  goto  " << WHITE_COLOR << code_chain->label() << '\n';
					break;
				}
				index = true;

				if (code_chain->has_label())
					os << GREEN_COLOR << code_chain->label() << ":\n" << WHITE_COLOR;

				// Concrete printer
				print_ir(*code_chain, os);

				if (code_chain->condition().has_value())
				{
					os << PURPLE_COLOR << ", goto " << WHITE_COLOR << code_chain->branching_label();
					auto& performed_branch = performed.at(code_chain->condition_ptr());
					if (!performed_branch)
						remaining_codes.push_back(code_chain->condition_ptr());
				}

				os << '\n';
				code_chain = code_chain->next();
				jmp = true;
			}

		}

		os << '\n';
	}
}
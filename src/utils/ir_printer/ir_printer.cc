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
		case ir_type::ModuloOperator:
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
		}

		os << "\t" << WHITE_COLOR;

		for (const auto& vreg: tac_code.operands())
			os << " R" << vreg;

		// Additional output

		switch (tac_code.get_type())
		{
		case ir::tac::type::Init:
			os << " \"" << tac_code.identifier() << "\" " << tac_code.value();
			break;
		default:;
			/* nothing */
		}
	}

	void print_ir(intermediate_representation::generation_unit& gunit, std::ostream& os)
	{
		struct data
		{
			std::vector<std::string> labels;
			bool is_done = false;
			bool is_referenced = false;
		};

		std::map<ir::tac*, data> source_index{};
		std::list<ir::tac*> remaining_codes{};

		auto add_label = [l = 0lu](data& d) mutable
		{
		  d.labels.push_back('L' + std::to_string(l++));
		};

		for (const auto& entry_point : gunit.entry_points())
		{
			remaining_codes.push_back(entry_point.second);
			source_index[entry_point.second].labels.push_back(CYAN_COLOR + entry_point.first);
		}

		for (const auto& tac: gunit.tacs())
		{
			if (tac->next())
			{
				auto& code_idx = source_index[tac->next()];

				if (code_idx.labels.empty() && code_idx.is_referenced)
					add_label(code_idx);

				code_idx.is_referenced = true;
			}

			if (tac->condition().has_value())
			{
				auto& code_idx = source_index[tac->condition().value()];

				if (code_idx.labels.empty())
					add_label(code_idx);
			}
		}

		while (!remaining_codes.empty())
		{
			ir::tac* code_chain = remaining_codes.front();
			remaining_codes.pop_front();

			bool jmp = false;

			while (code_chain)
			{
				auto& code_idx = source_index[code_chain];

				if (code_idx.is_done)
				{
					if (jmp)
						os << PURPLE_COLOR << "  jmp   " << WHITE_COLOR << code_idx.labels.front() << '\n';
					break;
				}

				code_idx.is_done = true;

				for (const auto& label: code_idx.labels)
					os << GREEN_COLOR << label << ":\n" << WHITE_COLOR;

				// Concrete printing function
				print_ir(*code_chain, os);

				if (code_chain->condition().has_value())
				{
					auto& branch_stats = source_index.at(code_chain->condition().value());
					os << PURPLE_COLOR << ", jmp " << WHITE_COLOR << branch_stats.labels.front();
					if (!branch_stats.is_done)
					{
						remaining_codes.push_front(code_chain->condition().value());
					}
				}
				os << '\n';

				code_chain = code_chain->next();
				jmp = true;
			}

		}
	}
}
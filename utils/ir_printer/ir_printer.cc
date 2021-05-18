#include "ir_printer.hh"
#include <ir_generation/ir_code.hh>
#include <iostream>
#include <list>

namespace ir = intermediate_representation;

namespace printer
{
	void print_ir(ir::tac* tac_code, std::ostream& os)
	{
		switch (tac_code->get_type())
		{
		case ir::tac::type::Nop:
			os << "\t" << "nop" << "\t";
			break;
		case ir::tac::type::Init:
			os << "\t" << "init" << "\t";
			break;
		case ir::tac::type::Add:
			os << "\t" << "add" << "\t";
			break;
		case ir::tac::type::Negate:
			os << "\t" << "neg" << "\t";
			break;
		case ir::tac::type::Copy:
			os << "\t" << "copy" << "\t";
			break;
		case ir::tac::type::Read:
			os << "\t" << "read" << "\t";
			break;
		case ir::tac::type::Write:
			os << "\t" << "write" << "\t";
			break;
		case ir::tac::type::Equals:
			os << "\t" << "eq" << "\t";
			break;
		case ir::tac::type::IfNotZero:
			os << "\t" << "ifnz" << "\t";
			break;
		case ir::tac::type::FunctionCall:
			os << "\t" << "fcall" << "\t";
			break;
		case ir::tac::type::Return:
			os << "\t" << "rtrn" << "\t";
			break;
		}
		for (auto u: tac_code->operands())
		{
			os << " R" << u;
		}
		if (tac_code->get_type() == ir::tac::type::Init)
		{
			os << "\"" << tac_code->identifier() << "\"" << tac_code->value();
		}
	}

	void print_ir(intermediate_representation::generation_unit& gunit, std::ostream& os)
	{
		struct data
		{
			std::vector<std::string> labels{};
			bool done{};
			std::size_t referred{};
		};

		std::map<ir::tac*, data> statistics{};
		std::list<ir::tac> remaining_statements{};

		auto add_label = [l = 0lu](data& d) mutable
		{
		  d.labels.push_back('L' + std::to_string(l++));
		};

		for (const auto& entry_point : gunit.entry_points())
		{
			remaining_statements.push_back(*entry_point.second);
			statistics[entry_point.second].labels.push_back(entry_point.first);
		}

		for (const auto& tac: gunit.tacs())
		{
			if (tac->next())
			{
				auto& t = statistics[tac->next()];

				if (t.labels.empty() && t.referred++)
				{
					add_label(t);
				}
			}
			if (tac->condition().has_value())
			{
				auto& t = statistics[tac->condition().value()];

				if (t.labels.empty())
				{
					add_label(t);
				}
			}
		}

		while (!remaining_statements.empty())
		{
			ir::tac* chain = &remaining_statements.front();
			remaining_statements.pop_front();
			for (bool needs_jmp = false; chain != nullptr; chain = chain->next(), needs_jmp = true)
			{
				auto& stats = statistics[chain];
				if (!stats.done)
				{
					if (needs_jmp)
					{
						os << "\tJMP " << stats.labels.front() << '\n';
					}
					stats.done = true;
					break;
				}

				for (const auto& l: stats.labels) os << l << ":\n";
				print_ir(chain, os);
				if (chain->condition().has_value())
				{
					auto& branch_stats = statistics[chain->condition().value()];
					os << ", JMP " << branch_stats.labels.front();
					if (!branch_stats.done)
					{
						remaining_statements.push_front(*chain->condition().value());
					}
				}
				os << '\n';
			}

		}
	}
}
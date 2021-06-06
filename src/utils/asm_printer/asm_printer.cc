#include <iostream>

#include <compiler/emitter.hh>
#include <iterator>
#include "asm_printer.hh"

constexpr const char* const WHITE = "\e[0m";
constexpr const char* const PURPLE = "\e[1;35m";
constexpr const char* const GREEN = "\e[1;32m";
constexpr const char* const CYAN = "\e[1;34m";
constexpr const char* const RED = "\e[1;31m";
constexpr const char* const ORANGE = "\e[1;33;3m";
constexpr const char* const BOLD = "";

namespace printer
{
	void print_instruction_selection(std::ostream& os, const compiler::emitter& emitter)
	{
		os << ORANGE << "After instruction selection\n\n" << WHITE;

		for (const auto& i :emitter.program())
		{
			if (i.label.has_value())
			{
				auto &[label_name, is_fun] = i.label.value();
				os << (is_fun ? PURPLE : CYAN) << label_name << WHITE << ":\n";
			}
			
			os << GREEN << '\t' << i.name << WHITE << "  ";

			for (const auto& v: i.virtual_operands)
				os << 'R' << v << ' ';

			if (i.int_literal.has_value())
				os << i.int_literal.value();
			else if (i.jmp_label.has_value())
				os << i.jmp_label.value();

			if (!i.precolored.empty())
			{
				os << RED << "\t; where";
				for (const auto &[key, value] : i.precolored)
					os << " R" << key << " is predefined as " << value;
			}
			os << WHITE << '\n';
		}

		os << '\n';
	}
}

#include <iostream>
#include <algorithm>
#include <iterator>

#include <compiler/emitter.hh>
#include "asm_printer.hh"

constexpr const char* const WHITE = "\e[0m";
constexpr const char* const PURPLE = "\e[1;35m";
constexpr const char* const GREEN = "\e[1;32m";
constexpr const char* const CYAN = "\e[1;34m";
constexpr const char* const RED = "\e[1;31m";
constexpr const char* const ORANGE = "\e[1;33;3m";
constexpr const char* const BOLD = "";

static int count_digits(int num)
{
	int digits = 0;
	while (num)
	{
		digits++;
		num /= 10;
	}
	return digits;
}

namespace printer
{
	void print_instruction_selection(std::ostream& os, const compiler::emitter& emitter)
	{
		if (!emitter.debug().functions.empty())
		{
			os << RED << "Stored functions\n\n" << WHITE;
			for (const auto &[reg, fun]: emitter.debug().functions)
				os << fun << " is \"stored\" in" << reg << '\n';
			os << '\n';
		}

		os << ORANGE << "After instruction selection\n\n" << WHITE;

		auto next_line = [line_counter = 0u, &os]() mutable -> void
		{
		  os << ORANGE << line_counter << '\t';
		  line_counter++;
		};

		for (const auto& i :emitter.debug().after_instruction_selection)
		{
			next_line();

			if (i.label.has_value())
			{
				auto &[label_name, is_fun] = i.label.value();
				if (!label_name.empty())
				{
					os << (is_fun ? PURPLE : CYAN) << label_name << WHITE << ":\n";
					next_line();
				}
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
				{
					os << " R" << key << " is predefined as %" << value << ';';
				}
			}
			os << WHITE << '\n';
		}

		os << '\n';
	}

	void print_basic_block(std::ostream& os, const compiler::emitter& emitter)
	{
		os << ORANGE << "Formed basic blocks\n\n" << WHITE;

		auto next_line = [line_counter = 0u, &os]() mutable -> void
		{
		  os << ORANGE << line_counter << '\t';
		  line_counter++;
		};

		auto const& prog = emitter.debug().after_instruction_selection;
		auto const& blocks = emitter.debug().last_formed_blocks;

		int line = 0;
		for (auto it = prog.cbegin(); it != prog.cend(); ++it)
		{
			line++;

			next_line();

			auto i = *it;
			if (i.label.has_value())
			{
				auto &[label_name, is_fun] = i.label.value();
				if (!label_name.empty())
				{
					os << (is_fun ? PURPLE : CYAN) << label_name << WHITE << ":\n";
					next_line();
				}
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
				{
					os << " R" << key << " is predefined as %" << value << ';';
				}
			}

			for (const auto& block: blocks)
			{
				if (block.begin_line == line)
					os << '\t' << ORANGE << "; Block #" << block.id << " begins" << WHITE;
				else if (block.end_line == line + 1)
					os << '\t' << ORANGE << "; Block #" << block.id << " ends";
			}

			os << WHITE << '\n';
		}

		os << '\n';

	}
}

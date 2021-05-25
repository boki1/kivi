#include <fstream>
#include <iostream>

#include <ast_printer/ast_printer.hh>
#include <cli/cli.hh>
#include <ir_generation/ir_code.hh>
#include <ir_printer/ir_printer.hh>
#include <parser/parser.tab.hh>
#include <parser/parsing_context.hh>

int main(int argc, const char *argv[])
{
	if (cli::parse_arguments(argc, argv))
		return 1;

	std::string file = argv[1];
	std::ifstream fstr(file);
	std::string buffer(std::istreambuf_iterator<char>(fstr), {});

	// PARSING
	sa::parsing_context ctx{buffer.c_str(), &file};
	yy::kivi_parser parser{ctx};
	parser.parse();

	if (cli::should_print(cli::pe::ast))
	{
		std::cout << printer::print(ctx.functions());
	}

	// Intermediate Representation
	intermediate_representation::generation_unit gu{};
	gu.generate(ctx.functions());

	if (cli::should_print(cli::pe::ir))
	{
		printer::print_ir(gu, std::cout);
	}

	// Assembly generation
	if (cli::should_print(cli::pe::asm_))
	{
		std::cout << "no asm yet :/\n";
	}

	return 0;
}

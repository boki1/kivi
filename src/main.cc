#include <fstream>
#include <iostream>

#include <ast_printer/ast_printer.hh>
#include <cli/cli.hh>
#include <ir_printer/ir_printer.hh>
#include <parser/parser.tab.hh>
#include <parser/parsing_context.hh>
#include <compiler/emitter.hh>
#include <arch/all.hh>
#include <arch/x86/x86_machine_target.hh>

int main(int argc, const char* argv[])
{
	if (cli::parse_arguments(argc, argv))
		return 1;

	std::string file = argv[1];
	std::ifstream fstr(file);
	std::string buffer(std::istreambuf_iterator<char>(fstr), {});

	// PARSING
	sa::parsing_context ctx{ buffer.c_str(), &file };
	yy::kivi_parser parser{ ctx };
	parser.parse();

	if (cli::should_print(cli::pe::ast))
	{
		std::cout << printer::print(ctx.functions());
	}

	// GENERATING INTERMEDIATE REPRESENTATION
	intermediate_representation::generation_unit irgen_unit{};
	irgen_unit.generate(ctx.functions());

	if (cli::should_print(cli::pe::ir))
	{
		printer::print_ir(irgen_unit, std::cout);
	}

	// COMPILING
	compiler::emitter{ compiler::default_target<compiler::x86>(), irgen_unit.fetch_output() };

	// Assembly generation
	if (cli::should_print(cli::pe::asm_))
	{
		std::cout << "\nno asm yet :/\n";
	}

	return 0;
}

#include <fstream>
#include <iostream>
#include <string_view>

#include <asm_printer/asm_printer.hh>
#include <ast_printer/ast_printer.hh>
#include <ir_printer/ir_printer.hh>
#include <cli/cli.hh>
#include <parser/parser.tab.hh>
#include <parser/parsing_context.hh>
#include <compiler/emitter.hh>
#include <arch/all.hh>
#include <arch/x86_64/x86_64_machine_target.hh>

void report(const std::string_view& error_message)
{
	std::cerr << error_message << '\n';
	exit(1);
}

int main(int argc, const char* argv[])
{
	if (cli::parse_arguments(argc, argv))
		return 1;

	std::string file = argv[1];
	std::ifstream fstr{ file };
	std::string buffer(std::istreambuf_iterator<char>(fstr), {});

	// PARSING
	sa::parsing_context ctx{ buffer.c_str(), &file };
	yy::kivi_parser parser{ ctx };
	if (parser.parse())
		report("FAILURE: Error occurred during parsing");

	if (cli::should_print(cli::pe::ast))
	{
		std::cout << printer::print(ctx.functions());
	}

	// GENERATING INTERMEDIATE REPRESENTATION
	intermediate_representation::generation_unit irgen_unit{};
	irgen_unit.generate(ctx.functions());
	auto TAC_sorted = irgen_unit.fetch_output();

	if (cli::should_print(cli::pe::ir))
		printer::print_ir(irgen_unit, std::cout);


	// COMPILING
	compiler::emitter x86_emitter{ compiler::configure_target<compiler::x86_64>(), TAC_sorted };
	if (!x86_emitter.select_instructions())
		report("FAILURE: Error during instruction selection");

	printer::print_instruction_selection(std::cout, x86_emitter);

	// Assembly generation
	if (cli::should_print(cli::pe::asm_))
	{
		std::cout << "\nno asm yet :/\n";
	}

	return 0;
}

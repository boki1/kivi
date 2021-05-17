#include <fstream>
#include <iostream>

#include <ast_printer/ast_printer.hh>
#include <cli/cli.hh>
#include <parser/parser.tab.hh>
#include <parser/parsing_context.hh>

int
main(int argc, const char* argv[])
{
	if (cli::parse_arguments(argc, argv))
	{
		return 1;
	}

	std::string file = argv[1];
	std::ifstream fstr(file);
	std::string buffer(std::istreambuf_iterator<char>(fstr), {});

	sa::parsing_context ctx{ buffer.c_str(), &file };

	yy::kivi_parser parser{ ctx };
	parser.parse();

	if (cli::should_print(cli::pe::ast))
	{
		std::cout << printer::print(ctx.functions());
	}

	if (cli::should_print(cli::pe::ir))
	{
		std::cout << "no ir yet :/\n";
	}
	
	if (cli::should_print(cli::pe::asm_))
	{
		std::cout << "no asm yet :/\n";
	}

	return 0;
}

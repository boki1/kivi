#include <fstream>
#include <iostream>

#include <parser/parser.tab.hh>
#include <parser/parsing_context.hh>
#include <ast_printer/ast_printer.hh>
#include <cli/cli.hh>
#include <ir_generation/ir_code.hh>
#include <ir_printer/ir_printer.hh>

int
main(int argc, char* argv[])
{
//	if (cli::argument_parser(argc, argv))
//	{
//		std::cout << "Bad usage\n";
//		return 1;
//	}

	std::string file = argv[1];
	std::ifstream fstr(file);
	std::string buffer(std::istreambuf_iterator<char>(fstr), {});

	sa::parsing_context ctx{ buffer.c_str(), &file };

	yy::kivi_parser parser{ ctx };
	parser.parse();

	std::cout << printer::print(ctx.functions());

    intermediate_representation::tac tac{};
    printer::print_ir(tac, std::cout);

	return 0;
}

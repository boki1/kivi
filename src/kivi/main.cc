#include <fstream>
#include <iostream>

#include <kivi_parser/kivi_parser.tab.hh>
#include <ast_printer/ast_printer.hh>

#include <ast/parsing_context.hh>

static void
usage()
{
	std::cout << "Use `kivi main.kv`" << '\n';
}

int
main(int argc, char* const argv[])
{
	if (argc != 2)
	{
		usage();
		return 0;
	}

	std::string filename = argv[1];
	std::ifstream ifs(filename);
	std::string code(std::istreambuf_iterator<char>(ifs), {});

	syntax_analyzer::parsing_context ctx(code.c_str(), &filename);
	yy::kivi_parser parser(ctx);
	parser.parse();
	std::vector<syntax_analyzer::function> functions = ctx.all_functions();

	parser_util::ast_printer ast_printer();


//	for (const auto& f : functions)
//		std::cout << f;

	return 0;
}


#include <iostream>
#include <fstream>

#include <parser/parser.tab.hh>
#include <parser/parsing_context.hh>

int
main(int argc, char* const argv[])
{
	if (argc != 2)
	{
		std::cout << "Bad usage\n";
		return 1;
	}

	std::string file = argv[1];
	std::ifstream fstr(file);
	std::string buffer(std::istreambuf_iterator<char>(fstr), {});

	sa::parsing_context ctx{ buffer.c_str(), &file };

	yy::kivi_parser parser{ ctx };
	parser.parse();

	return 0;
}

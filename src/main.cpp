#include <fstream>
#include <iostream>

#include "autogen/kivi_parser.tab.hh"
#include "include/parser.hpp"
#include "include/parsing_visualizer.hpp"

#define PARSING_VISUALIZATION_ENABLED

static void
usage ()
{
    std::cout << "Use `kivi main.kv`" << '\n';
}

std::ostream &
operator<< (std::ostream &os, const function &f)
{
    os << "Function < " << f.name << " >" << '\n';
    os << "# of Parameters = " << f.num_parameters << '\n';
    os << "# of Locals = " << f.num_locals << '\n';
    return os;
}

int
main (int argc, char *const argv[])
{
    if (argc != 2)
	{
	    usage ();
	    return 0;
	}

    const std::string filename = argv[1];
    std::ifstream ifs (filename);
    std::string code (std::istreambuf_iterator<char> (ifs), {});

    parsing_context ctx (code.c_str (), &filename);

    yy::kivi_parser parser (ctx);
    parser.parse ();
    std::vector<function> functions = std::move (ctx.get_function_list ());

    for (const auto &f : functions)
	{
	    std::cout << f;
	}

#ifdef PARSING_VISUALIZATION_ENABLED
    process_visualization::visualize_parsing (functions);
#endif

    return 0;
}


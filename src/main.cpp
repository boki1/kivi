#include <fstream>
#include <iostream>

#include "autogen/kivi_parser.tab.hh"
#include "include/parser.hpp"

static void
usage ()
{
    std::cout << "Use `kivi main.kv`" << '\n';
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

    return 0;
}

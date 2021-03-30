#include <fstream>
#include <iostream>

#include "autogen/kivi_parser.tab.hh"
#include "include/parser.hpp"
#include "include/parsing_visualizer.hpp"

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
        std::string stringified;
        for (const auto &f : functions)
        {
//            std::cout << "---------------------------------\n";
//
//            stringified = stringify(f);
//            unsigned current_tabs = 0;
//            for (int i = 0; i < stringified.size(); ++i) {
//                if (i != 0 && (stringified[i - 1] == '{' || stringified[i - 1] == ';' || stringified[i - 1] == '}')) {
//                    std::cout << "\n";
//                    if (stringified[i - 1] == '{') {
//                        ++current_tabs;
//                    }
//                    if (i != (stringified.size() - 1) - 1 && stringified[i + 1] == '}') {
//                        std::cout << "\n";
//                        --current_tabs;
//                    }
//                    for (int j = 0; j < current_tabs; ++j) {
//                        std::cout << "\t";
//                    }
//                    ++i;
//                }
//                std::cout << stringified[i];
//            }
//            std::cout << "\n";
        }
        visualize_parsing(functions);

    #endif
    return 0;
}


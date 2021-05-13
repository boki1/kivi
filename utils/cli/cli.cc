#include "cli.hh"
#include <iostream>
#include <list>
#include <loguru/loguru.hpp>

void
cli::options_set::usage() {
    std::cout << "Usage: kivi file.kv\n"
                 "run from the KIVI root directory. Example files can be found in the examples/ directory under the kivi root dir. "
                 "Welcome to the KIVI programming language! Here are some resources where you can find additional information about it:\n"
                 "- https://github.com/boki1/kivi;\n"
                 "- \n\n"
                 ""
                 "Here is the list of command line arguments that you can use:\n"
                 "-h, --help            shows this description\n"
                 "-v, --version         prints the version of the KIVI compiler on your machine\n"
                 "--compile-to=ASM|O    you can choose one of the following: assembly ('ASM' or 'asm') or object code ('O' or 'o'). \n"
                 "                      Your code will be compiled to the chosen one."
                 "--vis=AST|IR          You can also choose what visualization would you like. In order to use both, \n"
                 "                      run the command 2 times with the option you want";
}

void
cli::options_set::set_compile_to(cli::options_set::CompileToStage compileStage) {
    compile_to = compileStage;
    std::string stages[] = {"ASM", "OBJ"};
    LOG_F(INFO, "compile_to flag set to: '%s'\n", stages[static_cast<int>(compile_to)].c_str());
}

void
cli::options_set::recognize_compil_stage(std::string &&arg) {
    if (arg == "ASM" || arg == "asm") {
        set_compile_to(options_set::CompileToStage::ASM);
    } else if (arg == "OBJ" || arg == "obj") {
        set_compile_to(options_set::CompileToStage::O);
    } else {
        usage();
    }
}

void
cli::options_set::set_visualization_flags(cli::options_set::VisualizeFlagShift vis_flag_shift) {
    vis_flags |= 1 << static_cast<int>(vis_flag_shift);
    std::string stages[] = {"AST", "IR"};
    // TODO: visualize vis_flags bitmap
    LOG_F(INFO, "visualization option: '%s'\n", stages[static_cast<int>(vis_flag_shift)].c_str());
}

void
cli::options_set::recognize_visualization(std::string &&arg) {
    if (arg == "AST" || arg == "ast") {
        set_visualization_flags(options_set::VisualizeFlagShift::AST);
    } else if (arg == "IR" || arg == "ir") {
        set_visualization_flags(options_set::VisualizeFlagShift::IR);
    } else {
        usage();
    }
}

bool
cli::options_set::process_option(const std::string &&arg) {
    if (arg[0] != '-') { throw std::invalid_argument(""); }

    if (arg == "-h" || arg == "--help") {
        usage();
        return 1;

    } else if (arg == "-v" || arg == "--version") {
        std::cout << "0.0.1.\n";
        return 1;
    } else if (arg.substr(0, static_cast<const std::string>("--compile-to").length()) == "--compile-to") {
        const int prefix_length = static_cast<const std::string>("--compile-to").length();
        if (arg[prefix_length] == '=') {
            recognize_compil_stage(arg.substr(prefix_length + 1));
        } else {
            usage();
        }
    } else if (arg.substr(0, static_cast<const std::string>("--vis").length()) == "--vis") {
        const int prefix_length = static_cast<const std::string>("--vis").length();
        if (arg[prefix_length] == '=') {
            recognize_visualization(arg.substr(prefix_length + 1));
        } else {
            usage();
        }
    }
    return 0;
}

bool
cli::argument_parser(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    std::list<std::string> args_list;

    for (int i = 0; i < argc; ++i) {
        args_list.emplace_back(argv[i]);
    }

    struct cli::options_set enbl_options;

    for (const std::string &i : args_list) {
        try {
            if (enbl_options.process_option(static_cast<std::string>(i))) {
                break;
            }
        } catch (std::invalid_argument &exc) {
            continue;
        }
    }

    return 0;
}
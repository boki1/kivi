/**
 * @file cli/cli.hh
 * @brief This file provides the blueprint of the command line interface where
 * all utilities needed for it are placed. It is used for flags such as -h,
 * --help, -v, --version, etc.
 */

#ifndef _CLI_H_
#define _CLI_H_

#include <argparse/argparse.h>

using namespace argparse;

namespace cli
{

	struct settings
	{
		enum class verbosity : int
		{
			v0,
			v1,
			v2
		} verbosity_level{ verbosity::v0 };
		enum class print_stage_enum : int
		{
			ast,
			ir,
			asm_,
			all,
			none
		};
		print_stage_enum print_stage{ print_stage_enum::none };
		std::string output_file = "a.asm";
	} globals;

	using pe = settings::print_stage_enum;

	bool should_print(pe stage)
	{
		if (stage == pe::none)
			return false;

		return globals.print_stage == stage || globals.print_stage == pe::all;
	}

	bool parse_arguments(int argc, const char* argv[]) /* throws */
	{
		ArgumentParser parser("Kivi", "The Kivi programming language");

		parser.add_argument().names({ "-v", "--verbose" }).description("Display additional information while compiling");

		parser.add_argument()
			.names({ "-p", "--pprint" })
			.description("Pretty print a certain stage of the compilation process");

		parser.add_argument().names({ "-o", "--output" }).description("Define the output file of the compilation process");

		parser.enable_help();

		if (const auto& err = parser.parse(argc, argv))
		{
			std::cerr << "Bad usage: " << err << "\n";
			parser.print_help();
			return true;
		}

		if (parser.exists("help"))
		{
			parser.print_help();
			return true;
		}

		if (parser.exists("pprint"))
		{
			const auto& s = parser.get<std::string>("pprint");
			if (s == "asm")
				globals.print_stage = settings::print_stage_enum::asm_;
			else if (s == "all")
				globals.print_stage = settings::print_stage_enum::all;
			else if (s == "none")
				globals.print_stage = settings::print_stage_enum::none;
			else if (s == "ir")
				globals.print_stage = settings::print_stage_enum::ir;
			else if (s == "ast")
				globals.print_stage = settings::print_stage_enum::ast;
		}

		if (parser.exists("verbose"))
		{
			int v = parser.get<int>("verbose");
			globals.verbosity_level = static_cast<settings::verbosity>(v);
		}

		if (globals.verbosity_level == settings::verbosity::v2)
		{
			std::cout << "Argument parser configuration: \n";
			std::cout << "\tPrint " << static_cast<int>(globals.print_stage) << '\n';
			std::cout << "\tVerbosity level = " << static_cast<int>(globals.verbosity_level) << '\n';
			std::cout << "\tOutput file = " << globals.output_file << '\n';
		}

		return false;
	}

} // namespace cli
#endif // _CLI_H_

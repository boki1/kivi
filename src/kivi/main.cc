#include <fstream>
#include <iostream>

#define LOGURU_WITH_STREAMS 1
#include <loguru/loguru.hpp>

#include <ast/ast.hh>
#include <kivi_parser/kivi_parser.tab.hh>
#include <parser/parsing_context.hh>

static void
usage()
{
	std::cout << "Use `kivi main.kv`" << '\n';
}

/**
 * @brief Parse additional commands passed to the compiler
 * @param argc The number of arguments
 * @param argv The arguments themselves
 * @return True if the program should stop, else - if not.
 */
static bool
argument_parser(int argc, char* argv[])
{
	if (argc != 2)
	{
		LOG_S (INFO) << "'Help' argument provided" << std::endl;
		usage();
		return true;
	}

	return false;
}

/**
 * @brief Configures the logger
 * @param argc The number of arguments
 * @param argv The arguments themselves
 * @return True if the program should stop, else - if not.
 */
static bool
configure_loguro(int argc, char* argv[])
{
	loguru::init(argc, argv);
	loguru::add_file("build/logg.log", loguru::Append, loguru::Verbosity_MAX);
	loguru::add_file("build/logg_latest_readable.log", loguru::Truncate,
		loguru::Verbosity_INFO);
	loguru::g_stderr_verbosity = 1;

	// Throw exceptions instead of aborting on CHECK fails:
	loguru::set_fatal_handler([](const loguru::Message& message)
	{
	  throw std::runtime_error(std::string(message.prefix)
		  + message.message);
	});

	LOG_S (INFO) << "Logging configured" << std::endl;

	return false;
}

int
main(int argc, char* argv[])
{
	/// Configure and initialize
	if (configure_loguro(argc, argv))
		return 2;
	if (argument_parser(argc, argv))
		return 1;

	LOG_F (INFO, "Reading '%s'\n", argv[1]);
	std::string filename = argv[1];
	std::ifstream ifs{ filename };
	std::string code(std::istreambuf_iterator<char>{ ifs }, {});
	LOG_S (INFO) << "Dumping file contents...\n" << code << std::endl;

	syntax_analyzer::parsing_context ctx{ code.c_str(), &filename };
	/// Lexical and syntax analysis
	yy::kivi_parser parser{ ctx };
	parser.parse();

	/// AST
	auto functions = ctx.all_functions();
	syntax_tree::ast ast{ std::move(functions) };

	// ast_pprinter{ ast };
	// ast_pprinter.visit_all();

	/// IR code generation
	// ast_code_generator { ast };
	// ast_code_generator.visit_all();

	return 0;
}

#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <vector>

namespace test
{

struct variable_info
{
    ssize_t index;
    std::string name;
};

static const variable_info INCORRECT_VAR{ -1, "VarErr" };

struct function_info
{
    std::string name;
    std::vector<variable_info> locals;
    std::vector<variable_info> params;
};

// Kind of useless
static const function_info INCORRECT_FUNC{ "FuncErr", {}, {} };

static const std::map<std::string, std::vector<function_info> > TESTCASES{
    { "function_decl",
      { { "add_nums", {}, { { 0, "a" }, { 1, "b" } } },
	{ "sub_nums", {}, { { 0, "a" }, { 1, "b" } } } } },
    { "function_with_local",
      {
	  { "foo", { { 0, "c" } }, { { 0, "a" }, { 1, "b" } } },
      } },
    { "function_with_syntax_err",
      { { "foo", { INCORRECT_VAR }, { INCORRECT_VAR } } } }
};

}

static const std::string FILE_EXTENSTION = ".kv";
static const std::string BUILD_DIR = "../build/";
static const std::string TEST_DIR = "test/";
static const std::string EXECUTABLE = BUILD_DIR + "kivi";

/*
 *          Example output
 * ----------------------------------
 * test/function_decl.kv
 * ----------------------------------
 * Function < add_nums >
 * # of Parameters = 2
 * # of Locals = 0
 * Function < sub_nums >
 * # of Parameters = 2
 * # of Locals = 0
 * ----------------------------------
 * \n
 */

enum class OutputFormat
{
    SHORT,
    DETAILED
};

OutputFormat
format_from_str (const std::string &cst_str)
{
    std::string str (cst_str);
    std::transform (str.begin (), str.end (), str.begin (),
		    [] (unsigned char c) { return std::tolower (c); });

    if (str == "--short")
	return OutputFormat::SHORT;
    if (str == "--detailed")
	return OutputFormat::DETAILED;

    return OutputFormat::SHORT;
}

void
output_to (std::ostream &os, OutputFormat format)
{
    static const std::string separator
	= "----------------------------------\n";

    for (const auto &[filename, funcs] : test::TESTCASES)
	{
	    os << separator;
	    os << TEST_DIR + filename + FILE_EXTENSTION + "\n";
	    os << separator;

	    for (const auto &func : funcs)
		{
		    os << "Function < " << func.name << " >\n";

		    if (format == OutputFormat::DETAILED)
			{
			    os << "Locals...\n";

			    for (const auto &local : func.locals)
				{
				    os << local.index << ": " << local.name
				       << "\n";
				}

			    os << "Params...\n";
			    for (const auto &param : func.params)
				{
				    os << param.index << ": " << param.name
				       << "\n";
				}
			}
		    else
			{
			    os << "# of Parameters = " << func.params.size ()
			       << "\n";
			    os << "# of Locals = " << func.locals.size ()
			       << "\n";
			}
		}
	    os << separator << "\n";
	}
}

int
main (int argc, const char *argv[])
{
    using namespace test;

    std::ofstream os{ "CORRECT.txt", std::ios::out };
    auto format = format_from_str ((argc > 1) ? argv[2] : "");
    output_to (os, format);

    return 0;
}

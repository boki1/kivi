/**
 * @file error.cc
 * @brief Implements the "error()" function of the yy:kivi_parser
 */

#include <string>

#include "parser.tab.hh"

namespace sa = syntax_analyzer;

/**
 * @brief Reports an occurred syntactical error encountered during the parsing
 * process
 * @param p_location The location of the error
 * @param p_message The message which is outputted by the concrete error
 */
void
yy::kivi_parser::error (const location_type &p_location,
			const std::string &p_message)
{
    auto beg = p_location.begin;
    auto end = p_location.end;
    auto fname = beg.filename ? beg.filename->c_str () : "undefined file";

    std::cerr << fname;
    std::cerr << ':' << beg.line << ':' << beg.column << '-' << end.column << ": ";
    std::cerr << p_message << '\n';
}


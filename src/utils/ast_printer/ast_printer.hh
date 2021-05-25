/**
 * @file ast_printer.hh
 * @brief Defines functions for visualizing the generated AST
 */
#ifndef KIVI_UTILS_AST_PRINTER_AST_PRINTER_HH_
#define KIVI_UTILS_AST_PRINTER_AST_PRINTER_HH_

#include <string>
#include <utility>
#include <vector>

#include <textbox/textbox.hh>  //< 2D drawing

#include <parser/syntax.hh>    //< Syntactical structure definitions

namespace sa = syntax_analyzer;
using std::move;

namespace printer
{
	/**
	 * @brief Print all functions
	 * @return The string representation of the graph
	 */
	[[nodiscard]] std::string
	print(const std::vector<sa::function>&s) noexcept;

	/**
	 * @brief Print a concrete functions
	 * @param The function
	 * @return The string representation of the function
	 */
	[[nodiscard]] static std::string
	print(const sa::function&) noexcept;

	/**
	 * @brief Print a concrete expression
	 * @param The expression
	 * @return The string representation of the expression
	 */
	[[nodiscard]] static std::string
	print(const sa::expression&, bool is_statement = false) noexcept;

	/**
	 * @brief Print a concrete identifier
	 * @param The identifier
	 * @return The string representation of the identifier
	 */
	[[nodiscard]] static std::string
	print(const sa::identifier&) noexcept;

	/**
	 * @brief Prints an operation
	 * @param expr 	The operation
	 * @param oper	The stringified operator
	 * @param separator The separator between operands
	 * @note The separator is required to be of length 2 (at least)
	 * @return The string representation of the operation
	 */
	[[nodiscard]] static std::string
	print(const sa::expression&, const std::string& oper, const std::string& separator, bool is_statement = false, unsigned skip_first_n = 0) noexcept;
}

#endif //KIVI_UTILS_AST_PRINTER_AST_PRINTER_HH_

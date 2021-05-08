/**
 * @file string.hh
 *
 * Defines a string literal expression
 */
#ifndef KIVI_SRC_KIVI_EXPRESSIONS_STRING_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_STRING_HH_

#include <string>
#include <utility>

#include "literal.hh"

namespace syntax_analyzer
{

/**
 * String expression
 *
 * @brief Represents a string literal
 */
	class string_lit : public literal
	{
	 public:
		explicit string_lit(std::string f_str) :
			str(std::move(f_str)),
			literal(expression::kind::StringLiteral)
		{
		}

		explicit string_lit(const char* f_str) :
			str(f_str),
			literal(expression::kind::StringLiteral)
		{
		}

		const std::string&
		get_str() const noexcept
		{
			return str;
		}

		std::string
		to_string() const noexcept override
		{
			return get_str();
		}

	 private:
		/// The contained string literal value
		std::string str;
	};
}

#endif // KIVI_SRC_KIVI_EXPRESSIONS_STRING_HH_

//
// Created by Created by boki on 30.04.21 г..
//

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_STRING_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_STRING_HH_

#include <string>
#include <utility>

/**
 * @file string.hh
 * @brief Defines a class which represents a string literal expression
 */

#include "base_expression.hh"

namespace syntax_analyzer
{

	/**
	 * String expression
	 * @brief Represents a string literal
	 */
	class string_expression : expression
	{
	 public:
		explicit string_expression(std::string f_str) : str(std::move(f_str))
		{
		}

		explicit string_expression(const char* f_str) : str(f_str)
		{
		}

		const std::string& get_str() const noexcept
		{
			return str;
		}

		std::string to_string() const noexcept override
		{
			return get_str();
		}

	 private:
		/// The contained string literal value
		std::string str;
	};
}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_STRING_HH_

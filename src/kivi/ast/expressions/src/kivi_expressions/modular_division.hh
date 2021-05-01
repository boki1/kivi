/**
 * @file modular_diviosion.hh
 * @brief Defines the modular_diviosion operation expression class
 * @note Requires 2 operands (left and right)
 * @note Uses the `binary_expression` abstract class
 */

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_MODULAR_DIVISION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_MODULAR_DIVISION_HH_

#include "binary_expression.hh"

namespace syntax_analyzer
{

	/**
	 * An expression which represents modular division
	 */
	class modular_division_expression : binary_expression
	{
	 public:
		modular_division_expression() = default;

		modular_division_expression(value lhs, value rhs)
			: binary_expression(lhs, rhs)
		{
		}

	 public:
		std::string to_string() const noexcept override
		{
			return std::to_string(left()) + " % " + std::to_string(right());
		}
	};
}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_MODULAR_DIVISION_HH_

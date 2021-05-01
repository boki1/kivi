/**
 * @file multiplication.hh
 * @brief Defines the multiplication operation expression class
 * @note Requires 2 operands (left and right)
 * @note Uses the `binary_expression` abstract class
 */

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_MULTIPLICATION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_MULTIPLICATION_HH_

#include "binary_expression.hh"

namespace syntax_analyzer
{

	/**
	 * @brief An expression which represents multiplication
	 */
	class multiplication_expression : binary_expression
	{
	 public:
		multiplication_expression() = default;

		multiplication_expression(value lhs, value rhs)
			: binary_expression(left, right)
		{
		}

	 public:
		std::string to_string() const noexcept override
		{
			return std::to_string(left()) + " * " + std::to_string(right());
		}

	};
}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_MULTIPLICATION_HH_

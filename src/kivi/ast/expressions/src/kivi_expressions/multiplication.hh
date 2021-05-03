/**
 * @file multiplication.hh
 * @brief Defines the multiplication operation expression class
 * @note Requires 2 operands (left and right)
 * @note Uses the `binary_operation` abstract class
 */

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_MULTIPLICATION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_MULTIPLICATION_HH_

#include "binary_operation.hh"

namespace syntax_analyzer
{

	/**
	 * @brief An expression which represents multiplication
	 */
	class multiplication_expression : binary_operation
	{
	 public:
		multiplication_expression() = default;

		multiplication_expression(const value& lhs, const value& rhs)
			: binary_operation(lhs, rhs)
		{
		}

	 public:
		std::string to_string() const noexcept override
		{
//			return std::to_string(left()) + " * " + std::to_string(right());
			return "TODO";
		}

	};
}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_MULTIPLICATION_HH_

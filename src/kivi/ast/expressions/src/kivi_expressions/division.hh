/**
 * @file division.hh
 * @brief Defines the division operation expression class
 * @note Requires 2 operands (left and right)
 * @note Uses the `binary_operation` abstract class
 */

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_DIVISION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_DIVISION_HH_

#include "arithmetic_operation.hh"

namespace syntax_analyzer
{

	/**
	 * @brief An expression which represents the division operation
	 */
	class division_expression : I_arithmetic_operation
	{
	 public:
		division_expression() = default;

		division_expression(const value& lhs, const value& rhs)
			: I_arithmetic_operation(lhs, rhs)
		{
		}

	 public:
		std::string to_string() const noexcept override
		{
//			return std::to_string(left()) + " / " + std::to_string(right());
			return "TODO";
		}
	};
}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_DIVISION_HH_

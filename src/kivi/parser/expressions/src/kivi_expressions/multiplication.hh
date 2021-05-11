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
	class multiplication_expr : public arithmetic_operation
	{
	 public:
		multiplication_expr() = default;

		multiplication_expr(const value& lhs, const value& rhs)
			: arithmetic_operation(lhs, rhs, expression::kind::MultiplicationOper)
		{
		}

	 public:
		std::string
		to_string() const noexcept override
		{
			return "*";
		}
	};
}

#endif // KIVI_SRC_KIVI_EXPRESSIONS_MULTIPLICATION_HH_

/**
 * @file addition.hh
 * @brief Defines the addition operation expression class
 * @note Requires 2 operands (left and right)
 * @note Uses the `binary_operation` abstract class
 */

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_ADDITION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_ADDITION_HH_

#include "arithmetic_operation.hh"

namespace syntax_analyzer
{

	/**
	 * @brief A expression which represents the addition operation.
	 */
	class addition_expr : public arithmetic_operation
	{
	 public:
		addition_expr() = default;

		addition_expr(const value &left, const value &right) :
			arithmetic_operation(left, right, expression::kind::AdditionOper)
		{
		}

	 public:
		std::string to_string() const noexcept override
		{
			return "TODO";
		}
	};
}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_ADDITION_HH_

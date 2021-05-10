/**
 * @file addition.hh
 * @brief Defines the addition operation expression class
 * @note Requires 2 operands (left and right)
 * @note Uses the `binary_operation` abstract class
 */

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_ADDITION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_ADDITION_HH_

#include "binary_operation.hh"

namespace syntax_analyzer
{

	/**
	 * @brief A expression which represents the addition operation.
	 * @note Directly derives from `binary_operation`
	 */
	class addition_expr : public binary_operation
	{
	 public:
		addition_expr() = default;

		addition_expr(const value &left, const value &right)
			: binary_operation(left, right)
		{
		}

	 public:
		std::string to_string() const noexcept override
		{
//			return std::to_string(left()) + " + " + std::to_string(right());
			return "TODO";
		}
	};
}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_ADDITION_HH_

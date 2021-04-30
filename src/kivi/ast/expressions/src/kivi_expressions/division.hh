#ifndef KIVI_SRC_KIVI_EXPRESSIONS_DIVISION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_DIVISION_HH_


/**
 * @file division.hh
 * @brief Defines the division operation expression class
 * @note Requires 2 operands (left and right)
 * @note Uses the `binary_expression` abstract class
 */

#include "binary_expression.hh"

namespace syntax_analyzer
{

	class division_expression : binary_expression
	{
	 public:
		division_expression() = default;

		division_expression(int left, int right)
			: binary_expression(left, right)
		{
		}

	 public:
		std::string to_string() const noexcept override
		{
			return std::to_string(left()) + " / " + std::to_string(right());
		}
	};
}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_DIVISION_HH_

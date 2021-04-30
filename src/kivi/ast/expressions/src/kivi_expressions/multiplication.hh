//
// Created by Created by boki on 30.04.21 г..
//

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_MULTIPLICATION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_MULTIPLICATION_HH_


/**
 * @file multiplication.hh
 * @brief Defines the multiplication operation expression class
 * @note Requires 2 operands (left and right)
 * @note Uses the `binary_expression` abstract class
 */

#include "binary_expression.hh"

namespace syntax_analyzer
{

	class multiplication_expression : binary_expression
	{
	 public:
		multiplication_expression() = default;

		multiplication_expression(int left, int right) :
			binary_expression(left, right)
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

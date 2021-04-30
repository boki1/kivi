#ifndef KIVI_SRC_KIVI_EXPRESSIONS_BINARY_EXPRESSION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_BINARY_EXPRESSION_HH_

/**
 * @file binary_expression.hh
 * @brief Defines an abstract class which represents a binary operation expression.
 * @note Requires 2 operands (left and right)
 *
 * Used for implementing addition, multiplication and division
 */

#include "base_expression.hh"

namespace syntax_analyzer
{

	class binary_expression : expression
	{
	 protected:

		int m_lhs{};
		int m_rhs{};

	 public:

		binary_expression() = default;
		binary_expression(int lhs, int rhs)
			: m_lhs(lhs), m_rhs(rhs)
		{
		}

	 public:

		int left() const
		{
			return m_lhs;
		}

		int right() const
		{
			return m_rhs;
		}

	};

}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_BINARY_EXPRESSION_HH_

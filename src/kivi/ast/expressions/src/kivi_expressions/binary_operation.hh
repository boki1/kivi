/**
 * @file binary_operation.hh
 * @brief Defines an abstract class which represents a binary operation expression.
 * @note Requires 2 operands (left and right)
 *
 * Used for implementing addition, multiplication and division
 */

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_BINARY_EXPRESSION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_BINARY_EXPRESSION_HH_

#include "base.hh"

namespace syntax_analyzer
{

	/**
	 * @brief An expression which represents a binary operation
	 */
	class binary_operation : I_expression
	{
	 protected:

		/// The left hand-side of the expression
		value m_lhs;

		/// The right hand-side of the expression
		value m_rhs;

	 public:

		binary_operation() = default;

		binary_operation(const value& lhs, const value& rhs)
			: m_lhs(lhs), m_rhs(rhs)
		{
		}

	 public:

		const value& left() const
		{
			return m_lhs;
		}

		const value& right() const
		{
			return m_rhs;
		}

	};

}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_BINARY_EXPRESSION_HH_

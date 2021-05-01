#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_COMPARISON_EXPRESSION_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_COMPARISON_EXPRESSION_HH_

#include "binary_expression.hh"

namespace syntax_analyzer
{
	class comparison_expression : binary_expression
	{
	 protected:
		/// Stores the result from the comparison
		/// Initially set to 0.
		int m_result{};

	 public:
		comparison_expression() = default;

		comparison_expression(int left, int right)
			: binary_expression(left, right)
		{
		}

		virtual ~comparison_expression() = default;

	 public:

		/**
		 * @brief Evaluates the comparison operation
		 * @return 0 if values are equal
		 * @return -1 if left < right
		 * @return 1 if left > right
		 * @note **Potential bug:** Since we keep the lhs and rhs of the expression as simple integers if
		 * 		 					we compare identifiers the values of lhs and rhs does not get modified.
		 */
		int compare() noexcept {
			m_result = left() - right();
		}

	 public:
		int result()
		{
			return m_result;
		}

	};

}

#endif //KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_COMPARISON_EXPRESSION_HH_

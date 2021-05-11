/**
 * @file comparison_operation.hh
 * @brief Defines an interface which is responsible for handling all commonalities between comparison operations
 */

#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_COMPARISON_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_COMPARISON_HH_

#include "parser/syntactic_structure.hh"

#include "binary_operation.hh"

namespace syntax_analyzer
{
	class comparison_operation : public binary_operation
	{
	 protected:
		/// Stores the result from the comparison
		/// @note Initially set to 0.
		mutable int m_result{};

	 public:
		comparison_operation() = default;

		comparison_operation(const value& left, const value& right, expression::kind kind)
			: binary_operation(left, right, kind)
		{
		}

		virtual ~comparison_operation() = default;

		comparison_operation operator=(const expression &rhs) {
			return (*this);
		}

	 public:

		virtual /**
		 * @brief Evaluates the comparison operation
		 * @return 0 if values are equal
		 * @return -1 if left < right
		 * @return 1 if left > right
		 * @note This is the default definition of the compare function
		 * @note **Potential bug:** Since we keep the lhs and rhs of the expression as simple integers if
		 * 		 					we compare identifiers the values of lhs and rhs does not get modified.
		 * @note This is the "low-level" compare function. It gets called from the "high-level" compare functions
		 * defines in the deriving classes which map the result given from this one to the specific. For example the
		 * not equality_expr operator calls this function and than reverts the result.
		 */
		int compare() const noexcept
		{
			m_result = 0;
			// TODO:
			// Change m_result according to the ruleset
			// m_result = left() - right();
			return m_result;
		}

	 public:
		int result() const
		{
			return m_result;
		}

	};

}

#endif //KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_COMPARISON_HH_

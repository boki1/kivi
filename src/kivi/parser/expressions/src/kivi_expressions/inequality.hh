/**
 * @file inequality_expr.hh
 * @brief Defines a operation which checks for inequality_expr.
 */
#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_INEQUALITY_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_INEQUALITY_HH_

#include "parser/syntactic_structure.hh"

#include "comparison_operation.hh"

namespace syntax_analyzer
{

/**
 *  @brief Inequality operator
 *  @example
 *  ```
 *  if x <> y: ;
 *  ```
 */
	class inequality_expr : public comparison_operation
	{
	 public:
		inequality_expr() = default;
		inequality_expr(const value& lhs, const value& rhs) :
			comparison_operation(lhs, rhs, expression::kind::InequalityOper)
		{
		}

		int
		compare() const noexcept override
		{
			comparison_operation::compare();

			// Since the default behaviour of compare is to look for equality_expr
			// and we are checking whether the opposite is true we need to invert
			// the result - hence that.
			if (result() == -1)
				m_result = 1;
			if (result() == 1)
				m_result = -1;

			return m_result;
		}

		std::string to_string() const noexcept override
		{
			return "<>";
		}
	};

}

#endif // KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_INEQUALITY_HH_

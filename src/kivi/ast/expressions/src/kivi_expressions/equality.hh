/**
 * @file equality_expr.hh
 * @brief Defines a class which represents a equality_expr operation expression
 */
#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_EQUALITY_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_EQUALITY_HH_

#include <ast/syntactic_structure.hh>

#include "comparison_operation.hh"

namespace syntax_analyzer
{

/**
 * @brief Equality operator
 *
 * @example
 * ```
 * if x == y: ;
 * ```
 */
	class equality_expr : public comparison_operation
	{
	 public:
		equality_expr() = default;
		equality_expr(value lhs, value rhs) :
			comparison_operation(lhs, rhs, expression::kind::EqualityOper)
		{
		}

	 public:
		int
		compare() const noexcept override
		{
			return comparison_operation::compare();
		}
	};

}

#endif // KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_EQUALITY_HH_

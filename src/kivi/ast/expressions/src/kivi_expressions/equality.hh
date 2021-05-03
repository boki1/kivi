/**
 * @file equality.hh
 * @brief Defines a class which represents a equality operation expression
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
	class equality : I_comparison_operation
	{
	 public:
		equality() = default;
		equality(value lhs, value rhs)
			: I_comparison_operation(lhs, rhs)
		{
		}

	 public:
		int compare() const noexcept
		{
			return I_comparison_operation::compare();
		}

	};

}

#endif //KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_EQUALITY_HH_

/**
 * @file arithmetic_operation.hh
 * @brief Defines
 * @note This interface provides requires _no additional functionalities_ and is used only do denote that specific
 * binary operations are used for arithmetics
 * @note Consider changing such interfaces to c++20 concept
 */
#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_ARITHMETIC_OPERATION_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_ARITHMETIC_OPERATION_HH_

#include "binary_operation.hh"
#include "kivi_expressions/base.hh"

namespace syntax_analyzer
{
	/**
	 * An arithmetic operation
	 */
	class arithmetic_operation : public binary_operation
	{
	 public:
		arithmetic_operation() = default;

		arithmetic_operation(const value& lhs, const value& rhs, expression::kind kind) :
			binary_operation(lhs, rhs, kind)
		{
		}

		arithmetic_operation operator=(const expression& rhs)
		{
			return (*this);
		}

	};
}

#endif //KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_ARITHMETIC_OPERATION_HH_

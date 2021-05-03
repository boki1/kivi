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

namespace syntax_analyzer
{
	/**
	 * An arithmetic operation
	 */
	class I_arithmetic_operation : binary_operation
	{
	 public:
		I_arithmetic_operation() = default;

		I_arithmetic_operation(const value& lhs, const value& rhs)
			: binary_operation(lhs, rhs)
		{
		}
	};
}

#endif //KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_ARITHMETIC_OPERATION_HH_

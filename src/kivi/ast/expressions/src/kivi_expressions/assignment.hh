/**
 * @file assignment.hh
 * @brief Defines the assignment operation
 */
#ifndef KIVI_SRC_KIVI_EXPRESSIONS_ASSIGNMENT_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_ASSIGNMENT_HH_

#include <ast/syntactic_structure.hh>

#include "arithmetic_operation.hh"

namespace syntax_analyzer
{
	/**
	 * @brief An assignment operation
	 * @warning Potential bug: `binary_operation` stores 2 `value`'s as copies and not the originally passed ones.
	 * 			This is a problem since in order to affect the lhs, we need to keep a reference to it.
	 */
	class assignment_expr : public I_arithmetic_operation
	{
	 public:
		assignment_expr(const value& lvalue, const value& rvalue)
			: I_arithmetic_operation(lvalue, rvalue)
		{
		}
	};
}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_ASSIGNMENT_HH_

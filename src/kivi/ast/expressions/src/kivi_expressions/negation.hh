#ifndef KIVI_SRC_KIVI_EXPRESSIONS_NEGATION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_NEGATION_HH_

/**
 * @file negation.hh
 * @brief Defines a class which represents a numerical negation
 * @note Probably export a "unary_expression" class when additional support for unary operators is introduced
 */


#include <ast/syntactic_structure.hh>

#include "unary_operation.hh"

namespace syntax_analyzer
{
	class negation_expression : unary_operation
	{
	 public:
		negation_expression() = default;
		negation_expression(const value& operand)
			: unary_operation(operand)
		{
		}

	 public:
		std::string to_string() const noexcept override
		{
//			return std::to_string(operand());
			return "TODO";
		}
	};
}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_NEGATION_HH_

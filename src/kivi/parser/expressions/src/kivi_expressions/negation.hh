#ifndef KIVI_SRC_KIVI_EXPRESSIONS_NEGATION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_NEGATION_HH_

/**
 * @file negation.hh
 * @brief Defines a class which represents a numerical negation
 * @note Probably export a "unary_expression" class when additional support for
 * unary operators is introduced
 */

#include "parser/syntactic_structure.hh"

#include "unary_operation.hh"

namespace syntax_analyzer
{
	class negation_expr : public unary_operation
	{
	 public:
		explicit negation_expr(const value& operand) :
			unary_operation(operand, expression::kind::NegationOper)
		{
		}

	 public:
		[[nodiscard]] std::string
		to_string() const noexcept override
		{
			return "-";
		}
	};
}

#endif // KIVI_SRC_KIVI_EXPRESSIONS_NEGATION_HH_

/**
 * @file modular_diviosion.hh
 * @brief Defines the modular_diviosion operation expression class
 * @note Requires 2 operands (left and right)
 * @note Uses the `binary_operation` abstract class
 */

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_MODULAR_DIVISION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_MODULAR_DIVISION_HH_

#include "arithmetic_operation.hh"

namespace syntax_analyzer
{
/**
 * An expression which represents modular division
 */
	class modular_division_expr : public arithmetic_operation
	{
	 public:
		modular_division_expr() = default;

		modular_division_expr(value lhs, value rhs) :
			arithmetic_operation(lhs, rhs, expression::kind::ModularDivisionOper)
		{
		}

	 public:
		[[nodiscard]] std::string to_string() const noexcept override
		{
			return "%";
		}
	};
}

#endif // KIVI_SRC_KIVI_EXPRESSIONS_MODULAR_DIVISION_HH_

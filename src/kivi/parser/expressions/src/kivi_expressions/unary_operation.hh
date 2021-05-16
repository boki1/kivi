/**
 * @file unary_operation.hh
 *
 * Defines an abstract class from which all unary operations derive.
 */
#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_UNARY_OPERATION_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_UNARY_OPERATION_HH_

#include "parser/syntactic_structure.hh"

#include "base.hh"

namespace syntax_analyzer
{

	/**
	 * A unary operation representation via an abstract class
	 */
	class unary_operation : public expression
	{
	 private:
		/// The operand of operation
		value m_operand;

	 public:
		unary_operation(value operand, expression::kind kind)
			: expression(kind),
			  m_operand(operand)
		{
		}

		unary_operation()
		// TODO:
		//  Change
			: expression(expression::kind::NegationOper)
		{
		}

		virtual ~unary_operation() = default;

	 public:
		const value&
		operand() const noexcept
		{
			return m_operand;
		}
	};

}

#endif // KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_UNARY_OPERATION_HH_

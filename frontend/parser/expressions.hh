/**
 * @file expressions.cc
 * @brief Defines the "constructors" for all expressions
 */

#ifndef _KIVI_PARSER_EXPRESSIONS_HH
#define _KIVI_PARSER_EXPRESSIONS_HH

#include "syntax.hh"

using std::move;

namespace syntax_analyzer
{
	//
	// Terminals
	//

	/**
	 * @brief Construct a number literal expression
	 * @param num The value of the number
	 * @return Constructed expression
	 */
	inline expression
	number_literal(int num)
	{
		return expression(num);
	}

	/**
	 * @brief Define a string literal expression
	 * @param str The string value
	 * @return Constructed expression
	 */
	inline expression
	string_literal(std::string&& str)
	{
		return expression(move(str));
	}

	/**
	 * @brief Define an identifier expression
	 * @param ident The identifier
	 * @return Constructed expression
	 */
	inline expression
	identifier_expr(identifier&& ident)
	{
		return expression(move(ident));
	}

	/**
	 * @brief No operation expression
	 * @return Constructed expression
	 */
	inline expression
	nop_expr()
	{
		return expression(expression::type::Nop);
	}

	//
	// Unary operations
	//

	/**
	 * @brief Negation expression
	 * @param operand The operand to be negated
	 * @return Constructed expression
	 */
	inline expression
	negation_expr(expression&& operand)
	{
		return expression(expression::type::Negation, move(operand));
	}

	//
	// Binary operations
	//

	/**
	 * @brief Defines an addition operation expression
	 * @param lhs The left hand-side of the expression
	 * @param rhs The right hand-side of the expression
	 * @return Constructed expression
	 */
	inline expression
	addition_expr(expression&& lhs, expression&& rhs)
	{
		return expression(expression::type::Addition, move(lhs), move(rhs));
	}

	/**
	 * @brief Defines an multiplication operation expression
	 * @param lhs The left hand-side of the expression
	 * @param rhs The right hand-side of the expression
	 * @return Constructed expression
	 */
	inline expression
	multiplication_expr(expression&& lhs, expression&& rhs)
	{
		return expression(expression::type::Multiplication, move(lhs), move(rhs));
	}

	/**
	 * @brief Defines an modular division operation expression
	 * @param lhs The left hand-side of the expression
	 * @param rhs The right hand-side of the expression
	 * @return Constructed expression
	 */
	inline expression
	modular_division_expr(expression&& lhs, expression&& rhs)
	{
		return expression(expression::type::ModularDivision, move(lhs), move(rhs));
	}

	/**
	 * @brief Defines an division operation expression
	 * @param lhs The left hand-side of the expression
	 * @param rhs The right hand-side of the expression
	 * @return Constructed expression
	 */
	inline expression
	division_expr(expression&& lhs, expression&& rhs)
	{
		return expression(expression::type::Division, move(lhs), move(rhs));
	}

	/**
	 * @brief Defines an equality comparison operation expression
	 * @param lhs The left hand-side of the expression
	 * @param rhs The right hand-side of the expression
	 * @return Constructed expression
	 */
	inline expression
	equality_expr(expression&& lhs, expression&& rhs)
	{
		return expression(expression::type::Equality, move(lhs), move(rhs));
	}

	/**
	 * @brief Defines an inequality comparison operation expression
	 * @param lhs The left hand-side of the expression
	 * @param rhs The right hand-side of the expression
	 * @return Constructed expression
	 */
	inline expression
	inequality_expr(expression&& lhs, expression&& rhs)
	{
		const auto eq = expression(expression::type::Equality, move(lhs), move(rhs));
		return expression(expression::type::Equality, move(eq), 0);
	}

	/**
	 * @brief Defines an assignment operation expression
	 * @param lhs The left hand-side of the expression
	 * @param rhs The right hand-side of the expression
	 * @return Constructed expression
	 */
	inline expression
	assignment_expr(expression&& lhs, expression&& rhs)
	{
		return move(lhs).assign(move(rhs));
	}

	//
	// Special
	//

	/**
	 * @brief Defines a function call expression
	 * @tparam T Exptected (required) to be expression
	 * @param fun_name The function name
	 * @param parameters The parameters passed to the function
	 * @return Constructed expression
	 */
	template<typename ...T>
	inline expression
	function_call_expr(std::string&& fun_name, T&& ... parameters)
	{
		auto name = expression(identifier(identifier::type::Function, move(fun_name)));
		return expression(expression::type::FunctionCall, move(name), std::forward<T>(parameters)...);
	}

	/**
	 * @brief Defines a sequence of expressions
	 * @tparam T Expected (required) to be expression
	 * @param first The first (required) expression
	 * @param expressions The rest of the expressions
	 * @return Constructed expression
	 */
	template<typename ...T>
	inline expression
	sequence_expr(expression&& first, T&& ... expressions)
	{
		return expression(expression::type::Sequence, std::forward<T>(expressions)...);
	}

}

#endif //_KIVI_PARSER_EXPRESSIONS_HH
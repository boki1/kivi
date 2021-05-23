/**
 * @file expressions.cc
 * @brief Implements "constructors" for all expressions
 */

#ifndef _KIVI_PARSER_EXPRESSIONS_HH
#define _KIVI_PARSER_EXPRESSIONS_HH

#include <memory>

#include "syntactical_structures.hh"

using std::make_shared;
using std::move;

namespace syntax_analyzer
{
	expression
	number_literal(int num)
	{
		return expression(num);
	}

	expression
	string_literal(std::string&& str)
	{
		return expression(move(str));
	}

	expression
	identifier_expr(identifier&& ident)
	{
		return expression(move(ident));
	}

	expression
	nop_expr()
	{
		return expression(expression::type::Nop, {});
	}

	expression
	negation_expr(expression&& operand)
	{
		return expression(expression::type::Negation, { move(operand) });
	}

	expression
	addition_expr(expression&& lhs, expression&& rhs)
	{
		return expression(expression::type::Addition, { move(lhs), move(rhs) });
	}

	expression
	multiplication_expr(expression&& lhs, expression&& rhs)
	{
		return expression(expression::type::Multiplication, { move(lhs), move(rhs) });
	}

	expression
	modular_division_expr(expression&& lhs, expression&& rhs)
	{
		return expression(expression::type::ModularDivision, { move(lhs), move(rhs) });
	}

	expression
	division_expr(expression&& lhs, expression&& rhs)
	{
		return expression(expression::type::Division, { move(lhs), move(rhs) });
	}

	expression
	equality_expr(expression&& lhs, expression&& rhs)
	{
		return expression(expression::type::Equality, { move(lhs), move(rhs) });
	}

	expression
	inequality_expr(expression&& lhs, expression&& rhs)
	{
		const auto eq = expression(expression::type::Equality, { move(lhs), move(rhs) });
		return expression(expression::type::Equality, { eq, expression(0) });
	}

	expression
	assignment_expr(expression&& lhs, expression&& rhs)
	{
		return move(lhs).assign(move(rhs));
	}

	expression
	function_call_expr(std::string&& fun_name, expression&& parameter_list /* = {} */)
	{
		auto name = expression(identifier(identifier::type::Function, move(fun_name)));
		parameter_list.front_add(move(name));
		return expression(
			expression::type::FunctionCall,
			move(parameter_list.operands_copy())
		);
	}

	expression
	sequence_expr(expression&& first)
	{
		return expression(expression::type::Sequence, { move(first) });
	}

}

#endif //_KIVI_PARSER_EXPRESSIONS_HH
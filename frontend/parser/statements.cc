/**
 * @file statements.hh
 * @brief Implements "constructors" for all statements (if, while, return, compound)
 */
#ifndef KIVI_PARSER_STATEMENTS_HH_
#define KIVI_PARSER_STATEMENTS_HH_

#include "syntactical_structures.hh"

using std::move;

namespace syntax_analyzer
{
	expression
	if_stmt(expression&& condition, expression&& than_body)
	{
		return expression{ expression::type::If, { move(condition), move(than_body) }};
	}

	expression
	while_stmt(expression&& condition, expression&& loop_body)
	{
		return expression{ expression::type::While, { move(condition), move(loop_body) }};
	}

	expression
	return_stmt(expression&& retval)
	{
		return expression{ expression::type::Return, { move(retval) }};
	}

	expression
	return_stmt()
	{
		return expression{ expression::type::Return, { move(expression(0)) }};
	}

	expression
	compound_stmt()
	{
		return expression{ expression::type::Sequence, {}};
	}

}

#endif //KIVI_PARSER_STATEMENTS_HH_

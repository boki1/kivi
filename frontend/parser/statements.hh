#ifndef KIVI_PARSER_STATEMENTS_HH_
#define KIVI_PARSER_STATEMENTS_HH_

#include "syntax.hh"

using std::move;

namespace syntax_analyzer
{

	/**
	 * @brief Define an if-statement
	 * @param condition The condition of the if-statement
	 * @param than_body The body executed if the predicate is held
	 * @return Constructed expression
	 */
	inline expression
	if_stmt(expression&& condition, expression&& than_body)
	{
		return expression{ expression::type::If, move(condition), move(than_body) };
	}

	/**
	 * @brief Define a while-loop
	 * @param condition The condition of the while-loop
	 * @param loop_body The body executed if the predicate is help
	 * @return Constructed expression
	 */
	inline expression
	while_stmt(expression&& condition, expression&& loop_body)
	{
		return expression{ expression::type::While, move(condition), move(loop_body) };
	}

	/**
	 * @brief Define a return statement
	 * @param retval The value to be returned
	 * @return Constructed statement
	 */
	inline expression
	return_stmt(expression&& retval)
	{
		return expression{ expression::type::Return, move(retval) };
	}

	/**
	 * @brief Define a compound statement
	 * @tparam T Expected (required) to be expression
	 * @param first The first (mandatory) expression
	 * @param other The other expressions
	 * @return Constructed expression
	 */
	template<typename ...T>
	inline expression
	compound_stmt(expression&& first, T... other)
	{
		return expression{ expression::type::Sequence, first, std::forward<T>(other)... };
	}

}

#endif //KIVI_IR_FRONTEND_PARSER_STATEMENTS_HH_

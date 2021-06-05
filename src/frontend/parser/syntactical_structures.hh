/**
 * @file syntactic_structures.hh
 * @brief Declares the "constructors" for all _concrete_ syntactic structures
 */
#ifndef _KIVI_SYNTACTIC_STRUCTURES_HH_
#define _KIVI_SYNTACTIC_STRUCTURES_HH_

#include "syntax.hh"

using std::move;

namespace syntax_analyzer
{
/**
 * @brief Construct a number literal expression
 * @param num The value of the number
 * @return Constructed expression
 */
expression number_literal(int num);

/**
 * @brief Define a string literal expression
 * @param str The string value
 * @return Constructed expression
 */
expression string_literal(std::string &&str);

/**
 * @brief Define an identifier expression
 * @param ident The identifier
 * @return Constructed expression
 */
expression identifier_expr(identifier &&ident);

/**
 * @brief No operation expression
 * @return Constructed expression
 */
expression nop_expr();

/**
 * @brief Negation expression
 * @param operand The operand to be negated
 * @return Constructed expression
 */
expression negation_expr(expression &&operand);

/**
 * @brief Defines an addition operation expression
 * @param lhs The left hand-side of the expression
 * @param rhs The right hand-side of the expression
 * @return Constructed expression
 */
expression addition_expr(expression &&lhs, expression &&rhs);

/**
 * @brief Defines an multiplication operation expression
 * @param lhs The left hand-side of the expression
 * @param rhs The right hand-side of the expression
 * @return Constructed expression
 */
expression multiplication_expr(expression &&lhs, expression &&rhs);

/**
 * @brief Defines an modular division operation expression
 * @param lhs The left hand-side of the expression
 * @param rhs The right hand-side of the expression
 * @return Constructed expression
 */
expression modular_division_expr(expression &&lhs, expression &&rhs);

/**
 * @brief Defines an division operation expression
 * @param lhs The left hand-side of the expression
 * @param rhs The right hand-side of the expression
 * @return Constructed expression
 */
expression division_expr(expression &&lhs, expression &&rhs);

/**
 * @brief Defines an equality comparison operation expression
 * @param lhs The left hand-side of the expression
 * @param rhs The right hand-side of the expression
 * @return Constructed expression
 */
expression equality_expr(expression &&lhs, expression &&rhs);

/**
 * @brief Defines an inequality comparison operation expression
 * @param lhs The left hand-side of the expression
 * @param rhs The right hand-side of the expression
 * @return Constructed expression
 */
expression inequality_expr(expression &&lhs, expression &&rhs);

/**
 * @brief Defines an assignment operation expression
 * @param lhs The left hand-side of the expression
 * @param rhs The right hand-side of the expression
 * @return Constructed expression
 */
expression assignment_expr(expression &&lhs, expression &&rhs);

/**
 * @brief Defines a function call expression
 * @tparam T Expected (required); to be expression
 * @param fun_name The function name
 * @param parameter_list The parameters passed to the function as a separate expression
 * @return Constructed expression
 */
expression function_call_expr(std::string &&fun_name, const std::vector<function> &declared_functions, const function &current_function,
							  expression &&parameter_list = {});

/**
 * @brief Defines a sequence of expressions
 * @param first The current expression
 * @return Constructed expression
 */
expression sequence_expr(expression &&first);

/**
 * @brief Define an if-statement
 * @param condition The condition of the if-statement
 * @param than_body The body executed if the predicate is held
 * @return Constructed expression
 */
expression if_stmt(expression &&condition, expression &&than_body);

/**
 * @brief Define a while-loop
 * @param condition The condition of the while-loop
 * @param loop_body The body executed if the predicate is help
 * @return Constructed expression
 */
expression while_stmt(expression &&condition, expression &&loop_body);

/**
 * @brief Define a return statement
 * @param retval The value to be returned
 * @return Constructed statement
 */
expression return_stmt(expression &&retval);

/**
 * @brief Define an additional _implicit_ return statement
 * @return Expression with 'return 0' in it
 */
expression return_stmt();

/**
 * @brief Define a compound statement without preset arguments
 */
expression compound_stmt(std::vector<expression> body = {});
} // namespace syntax_analyzer

#endif // KIVI_SYNTACTIC_STRUCTURES_HH_

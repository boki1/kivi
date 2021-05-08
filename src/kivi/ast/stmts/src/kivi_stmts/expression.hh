/**
 * @file expression.h
 *
 * Defines the class representing an expression statement
 * syntactic structure.
 */
#ifndef KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_EXPRESSION_HH_
#define KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_EXPRESSION_HH_

#include <ast/syntactic_structure.hh>

#include "statement.hh"

namespace syntax_analyzer
{

	/**
	 * An expression statement
	 *
	 * ```
	 * _expression_;
	 * 1;
	 * "string";
	 * ```
	 */
	class expression_stmt : public statement
	{
	 private:
		/// The actual expression. Since all expressions can be evaluated, store a value.
		value m_expr;

	 public:
		explicit expression_stmt(const value& expr)
			: m_expr(expr),
			  statement(statement::kind::ExpressionStmt)
		{
		}

	 public:
		[[nodiscard]] const value& expr() const noexcept
		{
			return m_expr;
		}

		std::string to_string() const noexcept
		{
			// Intenionally empty
			return "";
		}

	};

}

#endif //KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_EXPRESSION_HH_

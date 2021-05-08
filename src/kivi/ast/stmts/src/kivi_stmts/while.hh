/**
 * @file while.hh
 *
 * Defines the class representing a while-loop statement
 * syntactic structure.
 */
#ifndef KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_WHILE_HH_
#define KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_WHILE_HH_

#include <ast/syntactic_structure.hh>

#include "statement.hh"

namespace syntax_analyzer
{

	/**
	 * A while-loop statement
	 *
	 * ```
	 * while _condition_: _statement_
	 * ```
	 */
	class while_stmt : public statement
	{
	 private:
		/// The condition required to be evaluated to true in order to execute the body
		value m_condition;

		/// The body executed if the condition is true
		statement m_than;

	 public:
		while_stmt(const value& condition, const statement& than)
			: m_condition(condition),
			  m_than(than),
			  statement(statement::kind::WhileStmt)
		{
		}

	 public:

		[[nodiscard]] const value& condition() const noexcept
		{
			return m_condition;
		}

		[[nodiscard]] const statement& than_body() const noexcept
		{
			return m_than;
		}

		[[nodiscard]] std::string to_string() const noexcept override
		{
			return "while";
		}
	};

}

#endif //KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_WHILE_HH_

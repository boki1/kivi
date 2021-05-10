/**
 * @file if.hh
 *
 * Defines the class representing a conditional statement
 * syntactic structure.
 */
#ifndef KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_IF_HH_
#define KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_IF_HH_

#include "parser/syntactic_structure.hh"

#include "statement.hh"

namespace syntax_analyzer
{

	/**
	 * A condition statement
	 *
	 * ```
	 * if _condition_: _statement_
	 * ```
	 */
	class if_stmt : public statement
	{
	 private:
		/// The condition required to be evaluated to true in order to execute the body
		value m_condition;

		/// The body executed if the condition is true
		statement m_than;

	 public:
		if_stmt(const value& condition, const statement& than)
			: m_condition(condition),
			  m_than(than),
			  statement(statement::kind::IfStmt)
		{
		}

	 public:
		[[nodiscard]] const value& condition() const noexcept
		{
			return m_condition;
		}

		const statement& than_body() const noexcept
		{
			return m_than;
		}

		[[nodiscard]] std::string to_string() const noexcept override
		{
			return "if";
		}

	};

}

#endif //KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_IF_HH_

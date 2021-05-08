/**
 * @file return.hh
 *
 * Defines the class representing a return statement
 * syntactic structure.
 */

#ifndef KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_RETURN_HH_
#define KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_RETURN_HH_

#include <ast/syntactic_structure.hh>

#include <kivi_expressions/numerical.hh>

#include "statement.hh"

namespace syntax_analyzer
{

	/**
	 * A return statement
	 *
	 * ```
	 * return <value>;
	 * ```
	 */
	class return_stmt : public statement
	{
	 private:
		/// The value returned
		value m_retval;

	 public:

		explicit return_stmt(const value& retval = sa::numerical_lit(0))
			: m_retval(retval),
			  statement(statement::kind::ReturnStmt)
		{
		}

	 public:
		[[nodiscard]] const value& retval() const noexcept
		{
			return m_retval;
		}

		[[nodiscard]] std::string to_string() const noexcept override
		{
			return "return";
		}

	};

}

#endif //KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_RETURN_HH_

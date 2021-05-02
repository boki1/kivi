/**
 * @file compound.hh
 *
 * Defines the class representing a compound statement
 * syntactic structure.
 */

#ifndef KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_COMPOUND_HH_
#define KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_COMPOUND_HH_

#include <vector>

#include <ast/syntactic_structure.hh>

#include "statement.hh"

namespace syntax_analyzer
{

	/**
	 * A compound statement
	 *
	 * ```
	 * {
	 *     1;
	 *     {
	 *
	 *     }
	 * }
	 * ```
	 */
	class compound_stmt : I_statement
	{
	 private:
		/// All contained statements
		std::vector<I_statement> m_body;

	 public:
		compound_stmt() = default;

		compound_stmt(const std::vector<I_statement>& body)
			: m_body(body)
		{
		}

	 public:

		const std::vector<I_statement>& body() const noexcept
		{
			return m_body;
		}

	};

}

#endif //KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_COMPOUND_HH_

/**
 * @file compound.hh
 *
 * Defines the class representing a compound statement
 * syntactic structure.
 */

#ifndef KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_COMPOUND_HH_
#define KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_COMPOUND_HH_

#include <utility>
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
	class compound_stmt : public I_statement
	{
	 private:
		/// All contained statements
		std::vector<I_statement> m_body;

	 public:
		compound_stmt() = default;

		explicit compound_stmt(std::vector<I_statement> body)
			: m_body(std::move(body))
		{
		}

		template<typename ...T>
		explicit compound_stmt(T&& ... args)
			: m_body({ std::forward<T>(args)... })
		{
		}

	 public:

		const std::vector<I_statement>& body() const noexcept
		{
			return m_body;
		}

		void append(I_statement&& stmt) noexcept
		{
			m_body.push_back(std::move(stmt));
		}

	};

}

#endif //KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_COMPOUND_HH_

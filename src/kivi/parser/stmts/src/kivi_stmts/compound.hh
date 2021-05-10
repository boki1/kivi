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

#include "parser/syntactic_structure.hh"

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
class compound_stmt : public statement
{
  private:
    /// All contained statements
    std::vector<statement> m_body;

  public:
    compound_stmt () = default;

    explicit compound_stmt (std::vector<statement> body)
	: m_body (std::move (body)), statement (statement::kind::CompoundStmt)
    {
    }

    template <typename... T>
    explicit compound_stmt (T &&...args)
	: m_body ({ std::forward<T> (args)... }),
	  statement (statement::kind::CompoundStmt)
    {
    }

  public:
    const std::vector<statement> &
    body () const noexcept
    {
	return m_body;
    }

    void
    append (statement &&stmt) noexcept
    {
	m_body.push_back (std::move (stmt));
    }

    [[nodiscard]] std::string
    to_string () const noexcept override
    {
	// Intentionally empty
	return "";
    }
};

}

#endif // KIVI_SRC_KIVI_AST_STMTS_SRC_KIVI_STMTS_COMPOUND_HH_

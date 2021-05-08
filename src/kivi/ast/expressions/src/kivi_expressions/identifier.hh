/**
 * @file identifier.hh
 *
 * Defines an identifier literal expression
 */
#ifndef KIVI_SRC_KIVI_EXPRESSIONS_IDENTIFIER_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_IDENTIFIER_HH_

#include <ast/syntactic_structure.hh>
#include <ast/syntax.hh>

#include <string>
#include <utility>

#include "literal.hh"

namespace syntax_analyzer
{
	class identifier_expr : public literal
	{
	 private:
		identifier m_ident;

	 public:
		identifier_expr() = default;

		explicit identifier_expr(identifier ident) :
			m_ident(std::move(ident)),
			literal(expression::kind::IdentifierExpr)
		{
		}

	 public:
		std::string
		to_string() const noexcept override
		{
			return m_ident.name();
		}

	 public:
		const identifier&
		ident() const noexcept
		{
			return m_ident;
		}

	};
}

#endif // KIVI_SRC_KIVI_EXPRESSIONS_IDENTIFIER_HH_

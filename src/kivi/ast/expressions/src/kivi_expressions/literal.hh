/**
 * @file terminal.hh
 *
 * Defines a class which represents a expression literal
 */
#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_LITERAL_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_LITERAL_HH_

#include <ast/syntactic_structure.hh>

#include "base.hh"

namespace syntax_analyzer
{

	/**
	 * An interface implemented by all expression literals -
	 * numerical, string and identifier
	 */
	class I_literal : I_expression
	{
	 public:
		virtual ~I_literal() = default;
	};

}

#endif //KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_LITERAL_HH_

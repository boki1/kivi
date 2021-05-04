/**
 * @file statement.hh
 * The file defines the `statement` interface.
 */

#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_STATEMENT_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_STATEMENT_HH_

#include <ast/syntactic_structure.hh>

namespace syntax_analyzer
{

	/**
	 * The statement interface
	 *
	 * All statement implement this.
	 */
	class I_statement : public I_syntactic_structure
	{

	 public:
		virtual ~I_statement() = default;
	};

}

#endif //KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_STATEMENT_HH_

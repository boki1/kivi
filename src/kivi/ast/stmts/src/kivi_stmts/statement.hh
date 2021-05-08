/**
 * @file statement.hh
 * The file defines the `statement` interface.
 */

#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_STATEMENT_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_STATEMENT_HH_

#include <string>

#include <ast/syntactic_structure.hh>

namespace syntax_analyzer
{

	/**
	 * The statement interface
	 *
	 * All statement implement this.
	 */
	class statement : public I_syntactic_structure
	{
	 public:
		enum class kind
		{
			IfStmt,
			WhileStmt,
			VarStmt,
			CompoundStmt,
			ReturnStmt,
			ExpressionStmt,
			Illegal
		};

	 private:
		kind m_kind;

	 public:
		/// Construction
		explicit statement(statement::kind kind_ = kind::Illegal)
			: m_kind(kind_)
		{
		}

		virtual ~statement() = default;

		virtual std::string to_string() const
		{
			return "TODO";
		}

	 public:
		statement::kind get_kind() const noexcept
		{
			return m_kind;
		}
	};

}

#endif //KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_STATEMENT_HH_

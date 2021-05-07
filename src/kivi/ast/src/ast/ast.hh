/**
 * @file ast.hh
 * @brief Provides definition for the AST class
 */
#ifndef KIVI_SRC_KIVI_AST_SRC_AST_AST_HH_
#define KIVI_SRC_KIVI_AST_SRC_AST_AST_HH_

#include <memory>
#include <vector>
#include <variant>

#include "syntax.hh"

namespace sa = syntax_analyzer;

namespace syntax_analyzer
{
	/**
	 * @brief This structure denotes _invalid_ syntactical structure
	 * @note Used only as a contained type inside the ast_node
	 */
	struct invalid_syntactical_structure
	{
		/// Empty (intentionally)
	};

	/// A shortcut.
	typedef invalid_syntactical_structure invalid;
}

namespace syntax_tree
{

	/// Forward-declaration of ast class
	class ast;

	enum class ast_node_kind
	{
		Program,
		SintacticalSignature
	};

	/**
	 * @brief This class represents a single node in the AST
	 */
	class ast_node
	{
	 private:
		/// The kind of node value stored in the concrete instance
		ast_node_kind m_kind;

		/// The children of the current node
		std::vector<ast_node> m_children;

		/// The value contained in the current node
		std::variant<sa::I_statement, sa::function, sa::identifier, sa::I_expression, sa::invalid> m_sem_value;

	 public:
		explicit ast_node(ast_node_kind kind)
			: m_kind(kind)
		{
		}

	 public:
		/**
		 * @brief Sets the passed arguments as children of the "this
		 * @param children The newly added children
		 * @return void
		 */
		void proceed_with(std::vector<ast_node>&& children)
		{

		}

		void proceed_with(ast_node&& child)
		{

		}

	};

	/**
	 * @brief This class represents the abstract syntax tree generated after the syntax analysis
	 */
	class ast
	{
	 private:
		/// Holds the root of the AST
		/// The currently supported syntax expects from a source file to have function statements in it. Since that is
		/// the case, in order to holds all nodes of the ast a single root node which is of type "Program" is required.
		/// Otherwise multiple AST's would be needed in order to keep the whole semantics of the program stored. Having
		/// such node as root, implies that all functions (since function definition inside another function is
		/// considered illegal) will be stored as children of this root node "Program".
		std::shared_ptr<ast_node> m_root{ new ast_node{ ast_node_kind::Program }};

	 public:
		explicit ast(std::vector<sa::function>&& functions)
		{
			for (auto const& fun: functions)
			{
				root_mut().proceed_with(extract(fun));
			}
		}

	 public:
		/// @brief "Extracts" the AST out of different kind of syntactical structures
		/// @param fun Function
		/// @return The root of the extracted AST
		static ast_node extract(const sa::function& fun);

		/// @brief "Extracts" the AST out of different kind of syntactical structures
		/// @param stmt Statement
		/// @return The root of the extracted AST
		static ast_node extract(const sa::I_statement& stmt);

		/// @brief "Extracts" the AST out of different kind of syntactical structures
		/// @param expr Expression
		/// @return The root of the extracted AST
		static ast_node extract(const sa::I_expression& expr);

		/// @brief "Extracts" the AST out of different kind of syntactical structures
		/// @param ident Identifier
		/// @return The root of the extracted AST
		static ast_node extract(const sa::identifier& ident);

	 public:
		ast_node& root_mut() noexcept
		{
			return *m_root;
		}
	};

}

#endif //KIVI_SRC_KIVI_AST_SRC_AST_AST_HH_

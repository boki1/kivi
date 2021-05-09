/**
 * @file ast.hh
 * @brief Provides definition for the AST class
 *
 * @todo Implement a const_iterator for AST. Consider avoiding code duplication by using inheritance.
 */
#ifndef KIVI_SRC_KIVI_AST_SRC_AST_AST_HH_
#define KIVI_SRC_KIVI_AST_SRC_AST_AST_HH_

#include <memory>
#include <vector>
#include <variant>
#include <stack>

#include <ast/syntactic_structure.hh>
#include <kivi_stmts/statement.hh>
#include <kivi_expressions/base.hh>

#include "syntax.hh"

namespace sa = syntax_analyzer;

namespace syntax_analyzer
{
	/**
	 * @brief This structure denotes _invalid_ syntactical structure
	 * @note Used only as a contained type inside the node
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

	struct Program
	{
	};

	/**
	 * @brief This class represents the abstract syntax tree generated after the syntax analysis
	 */
	class ast
	{
	 public:
		/// Forward declare the AST node class
		class node;

		/// Forward declare the AST node kind
		/**
			 * @brief Lists all kinds of value which may be stored inside a node of the AST
			 * @note Contains 2 additional kinds of values other than the syntactical structures defined by the grammar.
			 * These 2 are `Program` and `Illegal`. `Program` is used as a root of the AST, because the current legal syntax
			 * requires that a source file contains function definitions which contain the other syntactical structures inside
			 * their bodies.
			 * @note When `Illegal` is used, the semantic value inside the node is of type `syntax_analysis::illegal`.
			 */
		enum class node_kind
		{
			Program,
			Function,
			Identifier
		};

		typedef std::variant<sa::statement, sa::function, sa::identifier, sa::expression, sa::invalid> value_type;      //< The data type of contained value
		typedef std::variant<ast::node_kind, sa::expression::kind, sa::statement::kind> kind_type;                      //< The data type which combines the 3 "kind" enums
		typedef std::vector<ast::node> children_type;                                                                   //< The data type of children

	 public: /* Class node */
		/**
		 * @brief AST node
		 */
		class node
		{
		 private:
			/// The kind of node value stored in the concrete instance
			kind_type m_kind;

			/// The children of the current node
			children_type m_children;

			/// The value contained in the current node
			value_type m_value;

			/// Stringified
			std::string m_str = "";

		 public: /* Constructors & Destructors */

			/// Construction
			node(kind_type kind, const value_type& val, children_type preset_children = {})
				: m_kind(kind), m_value(val), m_children(std::move(preset_children))
			{
			}

			explicit node(const sa::identifier& ident);
			explicit node(const sa::function& fun);
			explicit node(const sa::statement& stmt);
			explicit node(const sa::expression& expr);

		 public: /* Functions */

			/**
			 * @brief Puts the given node as a child node to the current one
			 * @param child The child node
			 */
			void proceed_with(node child);

			/**
			 * @brief Puts the _extracted_ AST from the given syntactic structure as child to the current node
			 */
//			void proceed_with(const sa::I_syntactic_structure&);

		};

	 public: /* Class postorder_iterator */
		/**
		 * @brief AST postorder_iterator
		 * @note The class is marked as final
		 */
		class postorder_iterator final
		{
		private:
			///
			/// Iterator "configuration"
			/// Defines the iterator _traits_.
			///
			typedef ptrdiff_t difference_type;                       //< The difference between each element
			typedef ast::node value_type;                            //< The data type of the contained value
			typedef const ast::node& reference;                      //< The type of reference to the contained value
			typedef const ast::node* pointer;                        //< The type of pointer to the contained value
			typedef std::forward_iterator_tag iterator_category;     //< The type of postorder_iterator implementation

			// The pointer to an ast::node element
            pointer m_ptr;

        public: /* Constructors & Destructors */
		    explicit postorder_iterator(pointer ptr);

			/// Copy construction
			postorder_iterator(const ast::postorder_iterator&) = default;

            /// Destructor
            ~postorder_iterator() = default;

        public: /* Functions */
			/// Assignment operator
			postorder_iterator& operator=(const ast::postorder_iterator&);

			/// Prefix increment
			postorder_iterator& operator++();

			/// Postfix increment
			const postorder_iterator operator++(int);

			/// Lookup current position
			reference operator*() const;

			///
			pointer operator->() const;

			/// Equality operation
			friend bool operator==(const postorder_iterator&, const postorder_iterator&);

			/// Inequality operation
			friend bool operator!=(const postorder_iterator&, const postorder_iterator&);

			/// Swap function
			friend void swap(postorder_iterator& lhs, postorder_iterator& rhs);


		 public: /* Getters & Setters */
		    [[nodiscard]] pointer &get_ptr_mut() const;
		};

		/// Set the postorder depth-first search iterator as the default iterator
		typedef ast::postorder_iterator iterator;

	 public:

	 private:
		/** 
		 *  Holds the root of the AST
		 *  **NB:**
		 *  The currently supported syntax expects from a source file to have function statements in it. Since that is
		 *  the case, in order to holds all nodes of the ast a single root node which is of type "Program" is required.
		 *  Otherwise multiple AST's would be needed in order to keep the whole semantics of the program stored. Having
		 *  such node as root, implies that all functions (since function definition inside another function is
		 *  considered illegal) will be stored as children of this root node "Program".
		 */
		std::shared_ptr<node> m_root{ new node{
			node_kind::Program,
			sa::invalid()
		}};

	 public: /* AST Constructors & Destructors */
		explicit ast(std::vector<sa::function>&& functions)
		{
			for (auto const& fun: functions)
			{
				root_mut().proceed_with(ast::node(fun));
			}
		}

	 public: /* Functions */

		/** 
		 *  @brief "Extracts" the AST out of different kind of syntactical structures
		 *  @param ident Identifier
		 *  @return The root of the extracted AST
		 *  @note The extracted identifier looks this way as if in its AST representation
		 */
		static node extract(const sa::identifier& ident);

		/** 
		 *  @brief "Extracts" the AST out of different kind of syntactical structures
		 *  @param fun Function
		 *  @return The root of the extracted AST
		 */

		/**  @note About the "extracted" AST... The way that a function should be represented is the following:
		 *	```
		 *   	       function
		 *				  |
		 *	      -------------------
		 *        |                 |
		 *  parameter list		  body
		 *	```
		 * @note i.e The generated AST contains _at least_ 3 nodes: name, parameter list and the body of the function.
		 * @note "at least 3 nodes" is actually incorrect in regards to the detail since the body is at least 1 node as well.
		 */
		static node extract(const sa::function& fun);

		/** 
		 *  @brief "Extracts" the AST out of different kind of syntactical structures
		 *  @param stmt Statement
		 *  @return The root of the extracted AST
		 */

		/** @note About the so-called "extracted" AST... The way that a statement is represented solely depends on the concrete
		 *  statement. The options are these: If, While, Variable, Return, and Compound. Each of their representations is 
		 *  schematically illustrated here.
		 *  ```
		 *   		   if-statement
		 *      		    |
		 *          ------------------
		 *          |               |
		 *      condition         body
		 *  ```
		 *
		 *  ```
		 *   		  while-statement
		 *      		    |
		 *          ------------------
		 *          |               |
		 *      condition         body
		 *  ```
		 *
		 *  ```
		 *   		  return-statement
		 *      		    |
		 *          	    |
		 *      		 retval	
		 *  ```
		 *
		 *  ```
		 *   		  var-statement
		 *      		    |
		 *          ------------------
		 *          |               |
		 *      identifier		  value
		 *  ```
		 *
		 *  ```
		 *   		  compound-statement
		 *      		    |
		 *          		|
		 *      		  enter	
		 *					|
		 *				   ... (all contained statements)
		 *				    |
		 *      		  exit 
		 *  ```
		 */
		static node extract(const sa::statement& stmt);

		/** 
		 *  @brief "Extracts" the AST out of different kind of syntactical structures
		 *  @param expr Expression
		 *  @return The root of the extracted AST
		 */

		/**  @note Expressions differ in their concrete AST representation depending on the specific number of operands required.
		 *  There are 4 different types: binary operations, unary operations, terminal tokens and function calls. Each of their
		 *  AST forms is presented here:
		 *  ```
		 *   // Binary operation example with operator '+' 
		 *			    +
		 *      ----------------
		 *      |              |
		 *	operand1		operand2
		 *
		 *  ```
		 *
		 *  ```
		 *   // Unary operation example with operator '-' (its unary version of course :D)
		 *               -
		 *				 |
		 *			  operand
		 *  ```
		 *
		 *  ```
		 *	 // Terminal token example with string literal -- represented as is.
		 *		"string"	
		 *  ```
		 *
		 *  ```
		 *	 // Function call with N parameters (each of them is an expression)
		 *            <function_name>
		 *			----------------------------------------
		 *			|         |         |				   |
		 *		param1	   param2	 param3 	... 	paramN
		 *  ```
		 *
		 */
		static node extract(const sa::expression& expr);

		/**
		 *  @brief Gets whether the AST is empty or not
		 *  @return True if empty and false if not
		 */
		bool is_empty() const;

		/** 
		 *  @brief Gets an iterator to the beginning
		 *  @return Iterator to the beginning of the AST
		 */
		ast::iterator begin();

		/**
		 * @brief Gets an iterator to the end
		 * @return Iterator to the end of the AST
		 */
		ast::iterator end();

		/**
		 * @brief Gets the front node as an iterator
		 * @return The first node
		 */
		ast::iterator front();

		/**
		 * @brief Gets the last node as an iterator
		 * @return The last node
		 */
		ast::iterator back();

	 public: /* Getters & Setters */

		node&
		root_mut() noexcept
		{
			return *m_root;
		}

	};

	/// Iterator "swap" function
	/// @note **Cpp20 Potential bug** - check here:
	/// "Note that since C++20, specialization of functions from std namespace will not be allowed anymore.
	/// See [namespace.std.](http://eel.is/c++draft/namespace.std)" –- Stackoverflow
	void swap(ast::postorder_iterator& lhs, ast::postorder_iterator& rhs);

	/// Iterator equality operation
	bool operator==(const ast::postorder_iterator&, const ast::postorder_iterator&);

	/// Iterator inequality operation
	bool operator!=(const ast::postorder_iterator&, const ast::postorder_iterator&);

}

#endif //KIVI_SRC_KIVI_AST_SRC_AST_AST_HH_

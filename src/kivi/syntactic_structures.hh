#ifndef KIVI_PARSER_H
#define KIVI_PARSER_H

/* @file syntactic_structures.hh
 * @desc This file provides the blueprint for the parser implementation.
 * It defines helping classes that are used when parsing the given
 * source file such as `identifier` and `expression`. Here is also
 * defined a class called `parsing_context` which is used to hold
 * all the necessary information which is needed during the whole
 * parsing stage.
 */

#include <kivi_parser/location.hh>
#include <kivi_parser/stack.hh>

#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace syntax_analyzer
{

/// `enum identifier_type`
/// Represents each possible type of identifier which might
/// be met in a source file.
	enum class identifier_type
	{
		UNDEFINED,
		FUNCTION,
		PARAMETER,
		LOCAL
	};

/// `class identifier`
/// Used to represent a single identifier which is met in a source file.
/// Contains information such as its type (not data type, but type;
/// refer to `enum identifier_type` for more information), its name and
/// so forth.
	class identifier
	{
	 public:
		identifier() = default;

		identifier(identifier_type type, std::size_t index_within,
			std::string name)
			: m_type(type), m_index_within(index_within),
			  m_name(std::move(name))
		{
		}

	 public:
		[[nodiscard]] const std::string&
		get_name() const
		{
			return m_name;
		}

		[[nodiscard]] std::size_t
		get_index_within() const
		{
			return m_index_within;
		}

		[[nodiscard]] identifier_type
		get_ident_type() const
		{
			return m_type;
		}

	 private:
		/// `identifier::m_type`
		/// Used to store the type of the identifier
		identifier_type m_type = identifier_type::UNDEFINED;

		/// `identifier::m_index_within`
		/// Since the identifier is used as a parameter within parameter lists
		/// and as local variables within functions, it is important to know
		/// where it is located, hence -- index_within.
		std::size_t m_index_within = 0;

		/// `identifier::m_name`
		// Used to store the name of the identifier
		std::string m_name;
	};

/// `EXPRESSION_TYPES(o)`
/// This macro is used to enumerate all types of expressions.
/// The reason this macro exist is so that this enumeration happens only once
/// although it is actually used in other places as well.
/// The given argument `o` is used as a separator making it possible to use
/// the same macro definition for constructing functions which are
/// different for each expression type only by the name.
#define EXPRESSION_TYPES(o)                                                   \
    o (nop) o (string) o (number) o (identifier) o (addition) o (negation)    \
    o (equality) o (multiplication) o (division) o (modular_division)     \
        o (compare_and) o (compare_loop) o (function_call) o (copy)       \
        o (expression_sequence) o (retrn)

/// `enum class expression_type`
/// By using the defined `EXPRESSION_TYPES` macro, enumerate all valid
/// expression types.
#define o(n) n,
	enum class expression_type
	{
		EXPRESSION_TYPES (o)
	};
#undef o

/// `class expression`
/// Represents any expression which is met during parsing.
//	class expression
//	{
//	 public:
//		/// `template <typename... T> expression (expression_type t, T &&...args)`
//		/// *"with params" constructor*
//		/// Initializes a constructor with type T and push in the parameter list
//		/// all given parameters.
//		template<typename... T>
//		expression(expression_type t, T&& ...args)
//			: m_type(t), m_parameters{ std::forward<T>(args)... }
//		{
//		}
//
//		/// `expression()`
//		/// *"default" constructor* - nop expression
//		/// Initializes an expression which does nothing.
//		expression() : m_type(expression_type::nop)
//		{
//		}
//
//		/// `expression(identifier i)`
//		/// *"from identifier" constructor
//		/// Initializes an expression from identifier.
//		expression(identifier i)
//			: m_type(expression_type::identifier), m_identifier(std::move(i))
//		{
//		}
//
//		/// `expression(identifier &&i)`
//		/// *"from moved identifier" constructor
//		/// Initializes an expression from r-value identifier.
//		expression(identifier&& i)
//			: m_type(expression_type::identifier), m_identifier(std::move(i))
//		{
//		}
//
//		/// `explicit expression (std::string &&s)`
//		/// *"from string" constructor*
//		/// Initializes an expression from a string. Explicit since it would
//		/// not be pleased to get implict auto conversion on this one.
//		explicit expression(std::string&& s)
//			: m_type(expression_type::string), m_str_value(std::move(s))
//		{
//		}
//
//		/// `explicit expression (long v)`
//		/// *"from decimal" constructor
//		/// Initializes an expression from a decimal number.
//		/// Why explicit? Check "from string" constructor.
//		explicit expression(long v)
//			: m_type(expression_type::number), m_number_val(v)
//		{
//		}
//
//		// -- Getters ---
//
//		expression_type get_type() const;
//
//		const identifier& get_identifier() const;
//
//		const std::string& get_str_value() const;
//
//		long get_number_val() const;
//
//		const std::list<expression>& get_parameters() const;
//
//	 public:
//		/// `expression move_expr(expression &&b)`
//		/// *NB:* Takes an rvalue `this` argument
//		/// Moves an expression.
//		expression
//		move_expr(expression&& b)&&
//		{
//			return expression(expression_type::copy, std::move(b),
//				std::move(*this));
//		}
//
//		/// `void add_parameter(expression &&param)`
//		/// Pushed a moved parameter to the "parameter list" of the
//		/// current expression.
//		void
//		add_parameter(expression&& param)
//		{
//			m_parameters.push_back(param);
//		}
//
//		/// `void splice_parameter_list_with(expression &&other)`
//		/// Merges the "parameter lists" of other expression into the one
//		/// of `this` expression.
//		void splice_parameter_list_with(expression&& other);
//
//	 private:
//		expression_type m_type;
//		identifier m_identifier{};
//		std::string m_str_value{};
//		long m_number_val = 0;
//		std::list<expression> m_parameters;
//	};

	struct function
	{
		std::string name;
		expression code;
		unsigned num_locals = 0;
		unsigned num_parameters = 0;
	};

#define o(n)                                                                  \
    template <typename... T> inline expression new_##n##_expr (T &&...args)   \
    {                                                                         \
    return expression (expression_type::n, std::forward<T> (args)...);    \
    }
	EXPRESSION_TYPES (o)
#undef o

/// `class parsing_context`
/// This class is used as a container for all meta information which is
/// needed during the whole process of parsing the source files. It contains
// informations such as
	class parsing_context
	{
	 private:
		/// `vector<map<string, identifier>> m_scope_list`
		/// Denotes the scope level which is currently being parsed.
		/// The `identifier` instance is always of type `function`.
		std::vector<std::map<std::string, identifier> > m_scope_list;

		/// `vector<function< m_function_list`
		/// Contains all parsed functions.
		std::vector<function> m_function_list;

		/// `unsigned m_register_counter = 0`
		/// The number of the pseudo register in the following code generation step
		unsigned m_register_counter = 0;

		/// `function m_current_function`
		/// A `class function` instance about the current function which is being
		/// parsed
		function m_current_function;

	 public:
		/// const char *lexer_cursor
		/// yy::location location
		/// Used to hold the current location of the parser and lexer during
		/// the specific process.
		const char* lexer_cursor;
		yy::location location;

	 public:
		parsing_context(const char* code, std::string* filename)
			: lexer_cursor(code)
		{
			location.begin.filename = location.end.filename = filename;
		}

	 public:
		[[nodiscard]] const std::vector<function>&
		get_function_list() const
		{
			return m_function_list;
		}

	 public:
		/// `const identifier &define_identifier (const std::string &name,
		/// identifier &&f)` Defines an arbitary identifier type givena name
		/// and an r-value identifier. Also a check is made whether this
		/// identifier has already been created. A syntax error is thrown if a
		/// duplicate is seen.
		const identifier& define_identifier(const std::string& name,
			identifier&& f);

		/// `expression define_local (const std::string &name)`
		/// Defines a new local variable with the given name. The value
		/// of the `index_within` field is set to the number of local
		/// variables in the current function and this count is incremented.
		expression define_local(const std::string& name);

		/// `expression define_function (const std::string &name)`
		/// Defines a new function with the given name. The value
		/// of the `index_within` field is set to the number of already
		/// processed functions (`function_list.size()`).
		expression define_function(const std::string& name);

		/// `expression define_parameter (const std::string &name)`
		/// Defines a new parameter with the given name. The value
		/// of the `index_within` field is set to the number of the
		/// parameters in the parameter list and this number is increased.
		expression define_parameter(const std::string& name);

		/// `expression new_register_variable ()`
		/// Creates a new local variable (expression) with name "$I<reg_num>"
		expression new_register_variable();

		/// `expression use_identifier (const std::string &name) const`
		/// Use an arbitrary identifier with given name. If expression with
		/// this name is found it gets returned, otherwise an exception is
		/// thrown for undefiened identifier.
		[[nodiscard]] expression use_identifier(const std::string& name) const;

		/// `void add_function_with_block (...)`
		/// Define a function with given name and with given expression.
		void add_function_with_block(std::string&& name, expression&& code);

		/// `void enter_scope ()`
		/// Pushes an empty entry at the end of the `this->m_scope_list`
		void enter_scope();

		/// `void exit_scope ()`
		/// Pops the entry at the end of the `this->m_scope_list`
		void exit_scope();
	};

}

#endif

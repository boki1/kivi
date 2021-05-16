/**
 * @file syntax.hh
 *
 * @brief Defines all legal syntactic structures which may be encountered
 * during the process of parsing a source file. These are `identifier`,
 * `function` and `expression`.
 */
#ifndef _KIVI_SYNTAX_HH_
#define _KIVI_SYNTAX_HH_

#include <string>
#include <utility>
#include <variant>
#include <vector>
#include <memory>
#include <optional>

using std::move;

namespace syntax_analyzer
{

	/**
	 * @brief Structure which represents a syntactic structure. All syntactic
	 * structures derive from this.
	 */
	class syntactic_structure
	{
	 public:
		virtual ~syntactic_structure() = default;
	};

	/**
	 * The following data structure describes a valid identifier
	 * encountered during parsing of a source file. Check `identifier_class`
	 * for more information about the different types of identifiers.
	 */
	class identifier : public syntactic_structure
	{
	 public:
		/**
		 * Encountered identifiers may be used in different context, so
		 * in order to be aware of that, an additional classification is
		 * required. The following enumeration keeps track of the specific
		 * type of encountered identifier which may be used in different
		 * context.
		 */
		enum class type
		{
			Undefined, //< The identifier is used in unexpected and illegal way.
			Function,  //< The identifier is a function name
			Parameter, //< The identifier is a parameter in a function call
			Local      //< The identifier is a local variable in a function body
		};

	 private:
		/// The type of identifier
		identifier::type m_type = identifier::type::Undefined;

		/// The name of identifier
		std::string m_name;

		/// Since the identifier is stored as an operand in an operand list we
		/// keep the index within this list
		int m_index_within;

	 public:
		/// Default construction
		identifier() = default;

		/// Parameter construction
		identifier(identifier::type type, std::string&& name, int index = 0);

		/// Equals operator
		bool
		operator==(const identifier& other) const
		{
			return name() == other.name() &&
				get_type() == other.get_type();
		}

	 public:
		[[nodiscard]] identifier::type
		get_type() const noexcept
		{
			return m_type;
		}

		[[nodiscard]] int
		index() const noexcept
		{
			return m_index_within;
		}

		[[nodiscard]] const std::string&
		name() const noexcept
		{
			return m_name;
		}

		[[nodiscard]] std::string
		to_string() const noexcept
		{
			return name();
		}
	};

	/**
	 * @brief Structure which represents the syntactical structure expression
	 * @note The inner representation of statement is the same as expression.
	 */
	class expression : public syntactic_structure
	{
	 public:
		typedef std::variant<std::monostate, identifier, std::string, int> terminal_type; //< Used when representing a terminal expression
		typedef std::optional<std::shared_ptr<expression>> peculiar_type; //< Used for the "peculiar" field

		/**
		 * @brief Enumeration which marks the concrete type of expression which is
		 * contained.
		 * @note Each expression instance contains one of the values of
		 * expression::type
		 */
		enum class type
		{
			Nop,                //< No operation
			String,             //< String literal
			Number,             //< Number constant
			Identifier,         //< Identifier expression
			Addition,           //< Addition operation
			Negation,           //< Negation operation
			Multiplication,     //< Multiplication operation
			Division,           //< Division operation
			Equality,           //< Equality comparison operation
			ModularDivision,    //< Modular division operation
			Copy,               //< Copy expression
			If,                 //< If statement
			While,              //< While statement
			FunctionCall,       //< Function call operation
			Sequence,           //< Sequence of expressions
			Return,             //< Return statement
		};

	 private:
		//! In the operands of the expressions are contained all associated
		//! expressions which are required in order to successfully process "this"
		//! expression. Important note is that the supported statements are also
		//! represented as expression having (if one is present) their specific
		//! peculiarity stored in specific way.

		/// The operands associated with the concrete expression
		std::vector<expression> m_operands;

		/// The value of the expression if it is a terminal(Identifier, String or Number)
		expression::terminal_type m_terminal_value{};

		/// Used to store any special, specific operand such as the condition of
		/// the if statement, the condition of the while loop and the name of the
		/// function in a function call expression
		peculiar_type m_peculiar;

		/// Holds the specific type of expression
		expression::type m_type;

	 public:
		/// Default construction
		expression() = default;

		/// Default copy constructor
		expression(const expression&) = default;

		/// Default move constructor
		expression(expression&&) = default;

		/// Identifier expression constructor (move)
		explicit expression(identifier&& ident);

		/// Another identifier expression constructor (copying)
		explicit expression(const identifier& ident);

		/// String literal
		explicit expression(std::string&& str);

		/// Number constant literal
		explicit expression(int num);

		/// Manual construction
		expression(expression::type type, std::vector<expression>);

		/// Construction construction with "peculiar" field set
		expression(expression::type type, peculiar_type&&, std::vector<expression>);

		expression& operator=(const expression&) = default;

		bool operator==(const expression&) const noexcept;
		bool operator!=(const expression&) const noexcept;

	 public:

		/**
		 * TODO:
		 * @brief
		 * @param rhs
		 * @return
		 */
		expression
		assign(expression&& rhs)&&;

		/**
		 * @brief Appends an operand in the operands vector of the expression
		 * @param appendant The new operand
		 */
		void
		append(expression&& appendant);

		/**
		 * @brief Combines the operands of the expressions into the first one
		 * @param other The other one
		 */
		void
		merge_with(expression&& other);

	 public:

		[[nodiscard]] const std::vector<expression>&
		operands() const noexcept
		{
			return m_operands;
		}

		[[nodiscard]] std::vector<expression>
		operands_copy() const noexcept
		{
			return m_operands;
		}

		[[nodiscard]] const expression::terminal_type&
		terminal() const noexcept
		{
			return m_terminal_value;
		}

		[[nodiscard]] const expression::peculiar_type&
		peculiar() const noexcept
		{
			return m_peculiar;
		}

		[[nodiscard]] expression::type
		get_type() const noexcept
		{
			return m_type;
		}
	};

	/**
	 * The following data structure describes a valid function signature
	 * encountered during parsing of a source file.
	 */
	class function : public syntactic_structure
	{
	 private:
		/// The name of the function
		std::string m_name;

		/// The body of the function
		expression m_body;

		/// The number of local variables defined in the function body
		int m_locals{};

		/// The size of the parameter list of the function
		int m_parameters{};

	 public:
		/// Default construction
		function() = default;

		function(std::string&& name, expression&& body, int locals = 0, int parameters = 0);

		bool operator==(const function &other) const;

	 public:
		int add_local() noexcept
		{
			return m_locals++;
		}

		int add_param() noexcept
		{
			return m_parameters++;
		}

		void set_name(const std::string &name) noexcept {
			m_name = name;
		}

		void set_body(expression&& expr) noexcept {
			m_body = expr;
		}

	 public:
		[[nodiscard]] const std::string&
		name() const noexcept
		{
			return m_name;
		}

		[[nodiscard]] int
		locals() const noexcept
		{
			return m_locals;
		}

		[[nodiscard]] int
		parameters() const noexcept
		{
			return m_parameters;
		}

		[[nodiscard]] const expression&
		body() const noexcept
		{
			return m_body;
		}

		[[nodiscard]] std::string
		to_string() const noexcept
		{
			return m_name + "()";
		}
	};
}

#endif // KIVI_SRC_KIVI_SYNTAX_HH_

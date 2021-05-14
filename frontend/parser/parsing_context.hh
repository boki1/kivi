#ifndef KIVI_SRC_KIVI_PARSING_CONTEXT_HH_
#define KIVI_SRC_KIVI_PARSING_CONTEXT_HH_

/**
 * @file parsing_context.hh
 *
 * This class contains all information required and used during the process
 * of parsing a source file.
 */

#include <map>
#include <vector>

#define LOGURU_WITH_STREAMS 1
#include <loguru/loguru.hpp>

#include "parser.tab.hh"
#include "location.hh"

#include "syntax.hh"

using std::move;

namespace sa = syntax_analyzer;

namespace syntax_analyzer
{

/**
 * @brief An exception which is thrown when `exit_scope()` is called an no
 * active scopes have been entered
 */
	class cannot_pop_out_of_empty_exception : std::exception
	{
	};

	class parsing_context
	{
	 private:
		/// All parsed scopes
		std::vector<identifier> m_all_scopes;

		/// All parsed functions
		std::vector<function> m_all_functions;

		/// The current function that is being processed
		function m_this_function;

		/// The current number of "registers" being used
		int m_registers = 0;

		/**
		 * NB: The following 2 fields are public, because they are required by
		 * bison and re2c in order to keep track of the current location of the
		 * concrete process being executed. Because they are publicly visible, they
		 * do not follow the standard convention for field names - no "m_" prefix,
		 * and can be used without getters.
		 */
	 public:
		/// The location which is used and updated by the re2c module
		const char* lexer_cursor;

		/// The location which is used and updated by the bison module
		yy::location yy_location;

	 public:
		//
		// Constructors
		//

		/**
		 * @brief The constructor initializes the "location" variables in both the lexer and the parser
		 * @param code_beginning  the "location" var for the lexer
		 * @param filename the "location" var for the parser
		 */
		explicit parsing_context(const char* code_beginning, std::string* filename);

	 public:
		/**
		 * Pushes an empty entry at the end of scopes
		 * @return void
		 */
		void enter_scope();

		/**
		 * Pops the last entry from scopes
		 * @return void
		 * @throws `cannot_pop_out_of_empty_exception` when no active scopes have
		 * been entered
		 */
		void exit_scope() /* throws */;

		/**
		 * @brief Defines an arbitrary identifier
		 * @param ident Already instantiated identifier object
		 * @note Also a check is made whether this identifier has already been
		 * created.
		 * @throws A syntax error is thrown if a duplicate is seen.
		 * @return Identifier expression
		 */
		expression define_identifier(const identifier& ident);

		/**
		 * @brief Defines a new local variable inside a function body
		 * @param name The name of variable
		 * @return The newly created local variable
		 * @return Identifier (local) expression
		 */
		expression define_local(std::string&& name);

		/**
		 * @brief Defines a new function
		 * @param name The name of the function
		 * @return The newly created function
		 * @return Identifier (function) expression
		 */
		expression define_function(std::string&& name);

		/**
		 * @brief Defines a new parameter identifier
		 * @param name The name of the identifier
		 * @return The newly created parameter
		 * @return Identifier (parameter) expression
		 */
		expression define_parameter(std::string&& name);

		/**
		 * @brief Creates a new local variable with is going to be used as a IR
		 * register label
		 * @return The newly created local variable
		 * @return "Register" variable expression
		 */
		expression define_register();

		/**
		 * @brief Fetch the already defined identifier by a given name
		 * @param name The name of the identifier
		 * @return Reference to the found identifier
		 * @note It is _vitaly_ important that instead of the found identifier, an
		 * identifier expression is returned.
		 * @throws In case the identifier has not been already defined, an
		 * exception is thrown
		 */
		[[nodiscard]] expression use_identifier(const std::string& name) const;

		/**
		 * @brief Defines a function and associated expression body
		 * @param name The name of the function
		 * @param body The function body
		 * @return The newly placed function
		 */
		const function& define_function_body(std::string&& name, expression&& body);

	 public:
		[[nodiscard]] const std::vector<identifier>&
		all_scopes() const
		{
			return m_all_scopes;
		}

		std::vector<identifier>&
		all_scopes_mut()
		{
			return m_all_scopes;
		}

		[[nodiscard]] const std::vector<function>&
		all_functions() const
		{
			return m_all_functions;
		}

		[[nodiscard]] const function&
		this_function() const
		{
			return m_this_function;
		}

		[[nodiscard]] int
		registers() const
		{
			return m_registers;
		}
	};

}

#endif // KIVI_SRC_KIVI_PARSING_CONTEXT_HH_

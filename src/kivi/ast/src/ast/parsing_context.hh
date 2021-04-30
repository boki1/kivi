#ifndef KIVI_SRC_KIVI_PARSING_CONTEXT_HH_
#define KIVI_SRC_KIVI_PARSING_CONTEXT_HH_

/**
 * @file parsing_context.hh
 *
 * This class contains all information required and used during the process
 * of parsing a source file.
 */

#include <vector>
#include <map>

#include <kivi_parser/location.hh>
#include <kivi_parser/stack.hh>

#include "syntax.hh"

namespace syntax_analyzer
{

	class parsing_context
	{
	 private:
		std::vector<std::map<std::string, identifier>> m_all_scopes;
		std::vector<function> m_all_functions;
		function m_this_function;
		int m_registers = 0;

		const char* m_lexer_cursor;
		yy::location m_yy_location;

	 public:

		//
		// Constructors
		//

		/**
		 * The constructor initializes the "location" variables in both the
		 * lexer and the parser.
		 *
		 * @param code_beginning  the "location" var for the lexer
		 * @param filename the "location" var for the parser
		 */
		parsing_context(const char* code_beginning, std::string* filename)
			: m_lexer_cursor(code_beginning)
		{
			m_yy_location.begin.filename = filename;
			m_yy_location.end.filename = filename;
		}

	 public:
		///
		/// API
		///

		/**
		 * Pushes an empty entry at the end of scopes
		 * @return void
		 */
		void enter_scope();

		/**
		 * Pops the last entry from scopes
		 * @return void
		 */
		void exit_scope();

		/**
		 * @brief Defines an arbitrary identifier
		 * @param name The name of the new identifier
		 * @param ident R-value ref to already instantiated identifier object
		 * @note Also a check is made whether this identifier has already been created. * @throws A syntax error is thrown if a duplicate is seen.
		 * @return New identifier
		 */
		const identifier&
		define_identifier(const std::string& name, identifier&& ident);

		/**
		 * @brief Defines a new local variable inside a function body
		 * @param name The name of variable
		 * @return The newly created local variable
		 */
		void
		define_local(const std::string &name);

		/**
		 * @brief Defines a new function
		 * @param name The name of the function
		 * @return The newly created function
		 */
		void
		define_function(const std::string &name);

		/**
		 * @brief Defines a new parameter identifier
		 * @param name The name of the identifier
		 * @return The newly created parameter
		 */
		void
		define_parameter(const std::string &name);

		/**
		 * @brief Creates a new local variable with is going to be used as a IR register label
		 * @return The newly created local variable
		 * @param void
		 */
		void
		define_register();

		/**
		 * @brief Fetch the already defined identifier by a given name
		 * @param name The name of the identifier
		 * @return The found identifier
		 * @throws In case the identifier has not been already defined, an exception is thrown
		 */
		void
		use_identifier(const std::string &name) const;

		/**
		 * @brief Defines a function and associated expression body
		 * @param name the name of the function
		 * @param body the function body
		 * @return void
		 */
		void
		define_function_body(std::string &name, expression&& body);

	 public:
		///
		/// Getters
		///

		const std::vector<std::map<std::string, identifier>>& all_scopes() const
		{
			return m_all_scopes;
		}
		const std::vector<function>& all_functions() const
		{
			return m_all_functions;
		}
		const function& this_function() const
		{
			return m_this_function;
		}
		int registers() const
		{
			return m_registers;
		}
		const char* lexer_cursor() const
		{
			return m_lexer_cursor;
		}
		const yy::location& yy_location() const
		{
			return m_yy_location;
		}

	};

}

#endif //KIVI_SRC_KIVI_PARSING_CONTEXT_HH_
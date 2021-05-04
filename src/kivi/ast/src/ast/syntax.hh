/**
 * @file syntax.hh
 * @brief
 */

#ifndef KIVI_SRC_KIVI_SYNTAX_HH_
#define KIVI_SRC_KIVI_SYNTAX_HH_

/**
 * @file syntax.hh
 *
 * Defines all(1) legal syntactic structures which may be encountered during
 * the process of parsing a source file. These are `identifier`, `function` and
 * `expression`.
 *
 *
 * (1) Not exactly all. The `expression` is defined in different file.
 * Check `.hh` for more details.
 */

#include <string>
#include <utility>

#include <kivi_expressions/base.hh>

#include "syntactic_structure.hh"

namespace syntax_analyzer
{

	/**
	 * Encountered identifiers may be used in different context, so
	 * in order to be aware of that, an additional classification is
	 * required. This is the following enum, which keeps track of the
	 * specific type of the identifier.
	 * The different possibilities are self-explanatory.
	 */
	enum class identifier_class
	{
		/// The identifier is used in unexpected and illegal way.
		Undefined,
		/// The identifier is a function name
		Function,
		/// The identifier is a parameter in a function call
		Parameter,
		/// The identifier is a local variable in a function body
		Local,
	};

	/**
	 * The following data structure describes a valid identifier
	 * encountered during parsing of a source file. Check `identifier_class`
	 * for more information about the different types of identifiers.
	 */
	class identifier : I_syntactic_structure
	{
	 private:
		identifier_class m_type = identifier_class::Undefined;
		std::string m_name;

	 public:
		identifier() = default;
		identifier(identifier_class type, std::string name)
			: m_name(std::move(name)), m_type(type)
		{
		}

	 public:

		//
		// Getters
		//

		identifier_class type() const
		{
			return m_type;
		}

		const std::string& name() const
		{
			return m_name;
		}

	};

	/**
	 * The following data structure describes a valid function signature
	 * encountered during parsing of a source file.
	 */
	class function : I_syntactic_structure
	{
	 private:
		/// The name of the function
		std::string m_name;

		/// The body of the function
		I_statement m_body;

		/// The number of local variables defined in the function body
		int m_locals{};

		/// The size of the parameter list of the function
		int m_parameters{};

	 public:
		function() = default;

		function(const std::string& name, const I_statement& body, int locals, int parameters)
			: m_name{ name },
			  m_locals{ locals },
			  m_parameters{ parameters },
			  m_body{ body }
		{
		}

		function(const std::string& name, const I_statement& body)
			: m_name{ name },
			  m_body{ body },
			  m_parameters{},
			  m_locals{}
		{
		}

	 public:
		const std::string& name() const noexcept
		{
			return m_name;
		}

		int locals() const noexcept
		{
			return m_locals;
		}

		int parameters() const noexcept
		{
			return m_parameters;
		}

		const I_statement& body() const noexcept
		{
			return m_body;
		}

	};

}

#endif //KIVI_SRC_KIVI_SYNTAX_HH_

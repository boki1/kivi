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

#include <kivi_expressions/base_expression.hh>

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
		std::size_t m_index{};
		std::string m_name;

	 public:
		identifier() = default;
		identifier(identifier_class type, std::size_t index, std::string name)
			: m_name(std::move(name)), m_index(index), m_type(type)
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
		size_t index() const
		{
			return m_index;
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
		identifier m_name;

		/// The body of the function
		expression body;

		/// The number of local variables defined in the function body
		int m_locals{};

		/// The size of the parameter list of the function
		int m_parameters{};

	 public:
		function() = default;

		function(identifier name, /* expression body, */ int locals, int parameters)
			: m_name(std::move(name)), m_locals(locals), m_parameters(parameters)
		{
		}
	 public:
		const identifier& name() const
		{
			return m_name;
		}
		int locals() const
		{
			return m_locals;
		}
		int parameters() const
		{
			return m_parameters;
		}

	};

}

#endif //KIVI_SRC_KIVI_SYNTAX_HH_

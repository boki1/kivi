/**
 * @file base.hh
 *
 * The files defines the expression interface which all valid
 * expressions implement.
 */

#ifndef KIVI_SRC_KIVI_BASE_HH_
#define KIVI_SRC_KIVI_BASE_HH_

#include <string>
#include <list>

#include <ast/syntactic_structure.hh>

namespace syntax_analyzer
{
	/*
	 * An interface from which all concrete implementations of
	 * expression derive.
	 */
	class I_expression : public I_evaluable_syntactic_structure
	{
	 public:

		I_expression() = default;

		virtual ~I_expression() = default;

		/**
		 * Returns the string representation of the concrete expression
		 * @return string representation
		 */
		virtual std::string to_string() const noexcept
		{
			return "?";
		};

	};

}

#endif //KIVI_SRC_KIVI_BASE_HH_

/**
 * @file expressions.hh
 *
 * This file provides definitions of the classes which represent
 * each expression supported by the parser.
 */

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_HH_

#include <string>
#include <list>

#include "../../../ast/src/ast/syntactic_structure.hh"

namespace syntax_analyzer
{
	/*
	 * An abstract class from which all concrete implementations of
	 * expression derive.
	 */
	class expression : I_syntactic_structure
	{
	 public:
		/**
		 * The virtual destructor
		 */
		virtual ~expression() = default;

		/**
		 * Returns the string representation of the concrete expression
		 * @return string representation
		 */
		virtual std::string to_string() const noexcept
		{
			return "?";
		};

		/**
		 * @brief Adds a parameter to `this`'s parameter list
		 * @param param
		 * @note After calling this function with `param`, its value is no longer valid and should not be used.
		 * @return void
		 */
		virtual void add_parameter(expression&& param)
		{
			m_parameters.push_back(std::move(param));
		}

		/**
		 * @brief Splices merges the parameter lists of parameter expression with the `this`'s parameter list.
		 * @note After calling this function with `other`, its parameter list is no-longer valid.
		 * @param [in]other
		 * @return void
		 */
		virtual void splice_parameters(expression&& other)
		{
			m_parameters.splice(m_parameters.end(), std::move(m_parameters));
		}

	 protected:
		std::list<expression> m_parameters;
	};

}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_HH_

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_RETURN_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_RETURN_HH_

/**
 * @file return.hh
 * @brief Defines a class which represents a return expression
 */

#include "base_expression.hh"

namespace syntax_analyzer
{

	class return_expression : expression
	{
	 private:
		int m_retval;

	 public:
		return_expression() = default;

		return_expression(int retval)
			: m_retval(retval)
		{
		}

	 public:
		std::string to_string() const noexcept override
		{
			return std::to_string(retval());
		}

	 public:
		int retval() const noexcept
		{
			return m_retval;
		}

	};

}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_RETURN_HH_

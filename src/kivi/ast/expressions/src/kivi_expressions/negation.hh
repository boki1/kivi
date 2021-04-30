#ifndef KIVI_SRC_KIVI_EXPRESSIONS_NEGATION_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_NEGATION_HH_

/**
 * @file negation.hh
 * @brief Defines a class which represents a numerical negation
 * @note Probably export a "unary_expression" class when additional support for unary operators is introduced
 */

#include "base_expression.hh"

namespace syntax_analyzer
{
	class negation_expression : expression
	{
	 private:
		int m_num;

	 public:
		negation_expression() = default;
		negation_expression(int num)
			: m_num(num)
		{

		}

	 public:
		std::string to_string() const noexcept override
		{
			return std::to_string(num());
		}

	 public:
		int num() const noexcept
		{
			return m_num;
		}
	};
}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_NEGATION_HH_

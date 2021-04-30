#ifndef KIVI_SRC_KIVI_EXPRESSIONS_NOP_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_NOP_HH_

/**
 * @file nop.hh
 * @brief Defines a class which represents a nop expression
 * @note Does nothing :D
 */

#include "base_expression.hh"

namespace syntax_analyzer
{

	class nop_expression : expression
	{
	 public:
		std::string to_string() const noexcept override
		{
			return "nop";
		}
	};

}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_NOP_HH_

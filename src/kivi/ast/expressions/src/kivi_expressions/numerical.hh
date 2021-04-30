//
// Created by Created by boki on 30.04.21 г..
//

#ifndef KIVI_SRC_KIVI_EXPRESSIONS_NUMERICAL_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_NUMERICAL_HH_

#include "base_expression.hh"

namespace syntax_analyzer
{

	/**
	 * Numerical expression
	 * @brief Represents a number literal
	 */
	class numerical_expression : expression
	{
		explicit numerical_expression(long f_num) : num(f_num)
		{
		}
		explicit numerical_expression(int f_num) : num(f_num)
		{
		}
		explicit numerical_expression(double f_num) : num(f_num)
		{
		}

		std::string to_string() const noexcept override
		{
			return std::to_string(get_num());
		}

		long get_num() const noexcept
		{
			return num;
		}

	 private:
		/// The contained numerical literal value
		const long num;
	};

}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_NUMERICAL_HH_

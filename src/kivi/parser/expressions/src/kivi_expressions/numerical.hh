/**
 * @file numerical.hh
 *
 * Defines a numerical literal expression
 */
#ifndef KIVI_SRC_KIVI_EXPRESSIONS_NUMERICAL_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_NUMERICAL_HH_

#include "parser/syntactic_structure.hh"

#include "literal.hh"

namespace syntax_analyzer
{

/**
 * Numerical expression
 * @brief Represents a number literal
 */
	class numerical_lit : public literal
	{
	 public:
		explicit numerical_lit(int f_num) :
			num(f_num), literal(expression::kind::NumberLiteral)
		{
		}

		std::string
		to_string() const noexcept override
		{
			return std::to_string(get_num());
		}

		long
		get_num() const noexcept
		{
			return num;
		}

	 private:
		/// The contained numerical literal value
		const long num;
	};

}

#endif // KIVI_SRC_KIVI_EXPRESSIONS_NUMERICAL_HH_
/**
 * @file parameter_list.hh
 * @brief Defines a class which represents a function parameter list
 */
#ifndef KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_PARAMETER_LIST_HH_
#define KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_PARAMETER_LIST_HH_

#include <utility>
#include <vector>

#include <ast/syntactic_structure.hh>

#include "base.hh"

namespace syntax_analyzer
{

	/**
	 * @brief A function parameter list expression
	 */
	class parameter_list_expr : I_expression
	{
	 private:
		/// The parameters themselves. Each one is kept as a value instance
		std::vector<value> m_params;

	 public:

		parameter_list_expr() = default;

		parameter_list_expr(std::vector<value> params)
			: m_params(std::move(params))
		{
		}

	 public:
		const std::vector<value>& params() const noexcept
		{
			return m_params;
		}

	};

}

#endif //KIVI_SRC_KIVI_AST_EXPRESSIONS_SRC_KIVI_EXPRESSIONS_PARAMETER_LIST_HH_

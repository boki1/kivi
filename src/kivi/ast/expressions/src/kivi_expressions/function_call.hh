/**
 * @file function_call.hh
 * @brief Defines a class which represents a function call
 */
#ifndef KIVI_SRC_KIVI_EXPRESSIONS_FUNCTION_CALL_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_FUNCTION_CALL_HH_

#include <ast/syntactic_structure.hh>
#include <ast/syntax.hh>
#include <utility>

#include "parameter_list.hh"
#include "base.hh"

namespace syntax_analyzer
{
	class function_call_expr : I_expression
	{
	 private:
		identifier m_ident;
//		parameter_list_expr m_params;

	 public:
		function_call_expr() = default;

		function_call_expr(identifier ident/*, const parameter_list_expr &params */ )
			: m_ident(std::move(ident)) /*, m_params(params) */
		{
		}

	 public:
		const identifier& ident()
		{
			return m_ident;
		}

//		const parameter_list_expr &params() const noexcept {
//			return m_params;
//		}
	};
}

#endif //KIVI_SRC_KIVI_EXPRESSIONS_FUNCTION_CALL_HH_

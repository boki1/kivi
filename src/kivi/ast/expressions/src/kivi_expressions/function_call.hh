/**
 * @file function_call.hh
 * @brief Defines a class which represents a function call
 */
#ifndef KIVI_SRC_KIVI_EXPRESSIONS_FUNCTION_CALL_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_FUNCTION_CALL_HH_

#include <ast/syntactic_structure.hh>
#include <ast/syntax.hh>
#include <utility>

#include "base.hh"
#include "parameter_list.hh"

namespace syntax_analyzer
{
	class function_call_expr : public expression
	{
	 private:
		value m_ident;
		parameter_list_expr m_params;

	 public:
		function_call_expr() = default;

		explicit function_call_expr(const value& val)
			: m_ident(val),
			  m_params(),
			  expression(expression::kind::FunctionCallExpr)
		{
		}

		function_call_expr(const value& val, parameter_list_expr parlist)
			: m_ident(val),
			  m_params(std::move(parlist)),
			  expression(expression::kind::FunctionCallExpr)
		{
		}

	 public:
		const value&
		ident()
		{
			return m_ident;
		}

		const parameter_list_expr&
		params() const noexcept
		{
			return m_params;
		}
	};
}

#endif // KIVI_SRC_KIVI_EXPRESSIONS_FUNCTION_CALL_HH_

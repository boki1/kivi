/**
 * @file function_call.hh
 * @brief Defines a class which represents a function call
 */
#ifndef KIVI_SRC_KIVI_EXPRESSIONS_FUNCTION_CALL_HH_
#define KIVI_SRC_KIVI_EXPRESSIONS_FUNCTION_CALL_HH_

#include <sstream>

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
		std::string m_name;
		parameter_list_expr m_params;

	 public:
		function_call_expr() = default;

		explicit function_call_expr(std::string str)
			: m_name(std::move(str)),
			  m_params(),
			  expression(expression::kind::FunctionCallExpr)
		{
		}

		function_call_expr(std::string str, parameter_list_expr parlist)
			: m_name(std::move(str)),
			  m_params(std::move(parlist)),
			  expression(expression::kind::FunctionCallExpr)
		{
		}

	 public:
		const std::string&
		ident()
		{
			return m_name;
		}

		[[nodiscard]] const parameter_list_expr&
		params() const noexcept
		{
			return m_params;
		}

		/**
		 * @brief String repr of a function call
		 * @return "fun()" or "fun(...)" depending to whether any parameters are passed
		 */
		[[nodiscard]] std::string to_string() const noexcept override
		{
			std::stringstream sstr{ m_name };
			sstr << "(";
			if (!m_params.params().empty()) sstr << "...";
			sstr << ")";
			return sstr.str();
		}
	};
}

#endif // KIVI_SRC_KIVI_EXPRESSIONS_FUNCTION_CALL_HH_

/**
 * @file var.hh
 * @brief  Defines the var declaration statement
 */

#include <string>

#include <ast/syntax.hh>
#include <utility>

#include "statement.hh"

namespace syntax_analyzer
{

	/*
	 * @brief A var declaration
	 */
	class var_stmt : public statement
	{
	 private:
		std::string m_var;
		value m_val;

	 public:
		var_stmt(std::string var, const value& val)
			: m_var(std::move(var)),
			  m_val(val),
			  statement(statement::kind::VarStmt)
		{
		}

	 public:
		[[nodiscard]] const std::string& var() const noexcept
		{
			return m_var;
		}

		[[nodiscard]] const value& val() const noexcept
		{
			return m_val;
		}
	};

}

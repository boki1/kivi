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
	class var_stmt : public I_statement
	{
	 private:
		std::string m_var;
		value m_val;

	 public:
		var_stmt(std::string var, const value& val)
			: m_var(std::move(var)),
			  m_val(val)
		{
		}

		var_stmt() = default;
	};

}

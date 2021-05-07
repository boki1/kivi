#define LOGURU_WITH_STREAMS 1
#include <loguru/loguru.hpp>

#include <util/common.hh>
#include <kivi_parser/kivi_parser.tab.hh>

#include "parsing_context.hh"

/**
 * @file parsing_context.cc
 *
 * Implements the API of the `parsing_context` class.
 */

using kp = yy::kivi_parser;

namespace syntax_analyzer
{

	void parsing_context::enter_scope()
	{
		LOG_F(INFO, "Emplacing a new scope at the end\n");
		m_all_scopes.emplace_back();
	}

	void parsing_context::exit_scope()
	{
		LOG_F(INFO, "Popping last scope from the back\n");
		m_all_scopes.pop_back();
	}

	const identifier&
	parsing_context::define_identifier(const std::string& name, identifier&& ident)
	{
		LOG_S(INFO) << "Defining identifier \"" << name << "\"";
		auto it = all_scopes_mut().back().emplace(name, std::move(ident));

		if (!it.second)
		{
			LOG_S(WARNING) << "Duplicate definition of \"" + ident.name() << "\".";
			throw kp::syntax_error(yy_location, "Duplicate definition of \"" + ident.name() + "\".");
		}

		return it.first->second;
	}

	identifier_expr
	parsing_context::use_identifier(const std::string& name) const
	{
		LOG_S(INFO) << "Using identifier \"" + name << "\".";
		for (auto i = m_all_scopes.begin(); i < m_all_scopes.end(); ++i)
		{
			auto j = i->find(name);
			if (j != i->end())
			{
				return identifier_expr(j->second);
			}
		}

		LOG_S(WARNING) << "Unknown identifier \"" + name << "\".";
		throw kp::syntax_error(yy_location, "Unknown identifier \"" + name + "\"");
	}

	const function&
	parsing_context::define_function_body(const std::string& name, const I_statement& body)
	{
		/// Adds implicit return statement at the end of the block
		/// "concatenated" by this double-compound statement
		compound_stmt fun_body{ body, return_stmt() };

		LOG_S(INFO) << "Defining function (\"" + name << "\") with body (\"" << body.to_string() << "\")" << std::endl;
		m_all_functions.emplace_back(name, fun_body);
		return m_all_functions.back();
	}

	identifier parsing_context::define_local(const std::string& name)
	{
		LOG_S(INFO) << "Defining local variable (\"" + name << "\")" << '\n';
		return define_identifier(name, identifier(identifier_class::Local, name));
	}

	identifier parsing_context::define_function(const std::string& name)
	{
		LOG_S(INFO) << "Defining function (\"" + name << "\")" << '\n';
		return define_identifier(name, identifier(identifier_class::Function, name));
	}

	identifier parsing_context::define_parameter(const std::string& name)
	{
		LOG_S(INFO) << "Defining parameter (\"" + name << "\")" << '\n';
		return define_identifier(name, identifier(identifier_class::Parameter, name));
	}

	identifier parsing_context::define_register()
	{
		std::string name = "$L" + std::to_string(m_registers++);
		LOG_S(INFO) << "Defining register (\"" + name << "\")" << '\n';
		return define_local(name);
	}

}
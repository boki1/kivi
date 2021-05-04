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
		m_all_scopes.emplace_back();
	}

	void parsing_context::exit_scope()
	{
		m_all_scopes.pop_back();
	}

	const identifier&
	parsing_context::define_identifier(const std::string& name, identifier&& ident)
	{

		auto it = all_scopes_mut().back().emplace(name, std::move(ident));

		if (!it.second)
		{
			throw kp::syntax_error(yy_location, "Duplicate definition of \"" + ident.name() + "\".");
		}

		return it.first->second;
	}

	identifier parsing_context::use_identifier(const std::string& name) const
	{
		for (auto i = m_all_scopes.begin(); i < m_all_scopes.end(); ++i)
		{
			auto j = i->find(name);
			if (j != i->end())
			{
				return j->second;
			}
		}

		throw kp::syntax_error(yy_location, "Unknown identifier \"" + name + "\"");
	}

	const function&
	parsing_context::define_function_body(const std::string& name, I_statement&& body)
	{
		/// Adds implicit return statement at the end of the block
		/// "concatenated" by this double-compound statement
		compound_stmt fun_body{ std::move(body), return_stmt() };

		m_all_functions.emplace_back(name, fun_body);
		return m_all_functions.back();
	}

	identifier parsing_context::define_local(const std::string& name)
	{
		return define_identifier(name, identifier(identifier_class::Local, name));
	}

	identifier parsing_context::define_function(const std::string& name)
	{
		return define_identifier(name, identifier(identifier_class::Function, name));
	}

	identifier parsing_context::define_parameter(const std::string& name)
	{
		return define_identifier(name, identifier(identifier_class::Parameter, name));
	}

	identifier parsing_context::define_register()
	{
		return define_local("$L" + std::to_string(m_registers++));
	}
}
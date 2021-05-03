#include <util/common.hh>

#include "parsing_context.hh"

/**
 * @file parsing_context.cc
 *
 * Implements the API of the `parsing_context` class.
 */

namespace syntax_analyzer
{

	void parsing_context::enter_scope()
	{
		Unimplemented();
	}

	void parsing_context::exit_scope()
	{
		Unimplemented();
	}

	const identifier& parsing_context::define_identifier(const std::string& name, identifier&& ident)
	{
		Unimplemented();
	}

	void parsing_context::define_function_body(std::string& name, I_expression&& body)
	{
		Unimplemented();
	}
	void parsing_context::use_identifier(const std::string& name) const
	{
		Unimplemented();
	}
	void parsing_context::define_local(const std::string& name)
	{
		Unimplemented();
	}

	void parsing_context::define_function(const std::string& name)
	{
		Unimplemented();
	}

	void parsing_context::define_parameter(const std::string& name)
	{
		Unimplemented();
	}

	void parsing_context::define_register()
	{
		Unimplemented();
	}
}

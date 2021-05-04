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

	identifier parsing_context::define_identifier(const std::string& name, identifier&& ident)
	{
		Unimplemented();
		return identifier();
	}

	function parsing_context::define_function_body(const std::string& name, I_statement&& body)
	{
		Unimplemented();
		return function();
	}

	identifier& parsing_context::use_identifier(const std::string& name) const
	{
		Unimplemented();
	}

	identifier parsing_context::define_local(const std::string& name)
	{
		Unimplemented();
		return identifier();
	}

	function parsing_context::define_function(const std::string& name)
	{
		Unimplemented();
		return function();
	}

	identifier parsing_context::define_parameter(const std::string& name)
	{
		Unimplemented();
		return identifier();
	}

	int parsing_context::define_register()
	{
		Unimplemented();
		return -1;
	}
}

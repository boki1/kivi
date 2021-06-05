#include <algorithm>

#define LOGURU_WITH_STREAMS 1
#include <loguru/loguru.hpp>

#include "parser.tab.hh"
#include "parsing_context.hh"
#include "syntactical_structures.hh"
#include "syntax.hh"

/**
 * @file parsing_context.cc
 * @brief Implements the API of the `parsing_context` class.
 */

using kp = yy::kivi_parser;
using std::move;

namespace syntax_analyzer
{
	parsing_context::parsing_context(const char* code_beginning,
		std::string* filename)
		: lexer_cursor(code_beginning)
	{
		yy_location.begin.filename = filename;
		yy_location.end.filename = filename;

//		if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//			LOG_F (INFO, "Initializing parsing_context\n");
	}

	void
	parsing_context::enter_scope()
	{
//		if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//			LOG_F (INFO, "Placing a new scope at the end\n");
		m_scopes.emplace_back();
	}

	void
	parsing_context::exit_scope()
	{
		if (m_scopes.empty())
		{
//			if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//				LOG_F (WARNING, "Popping last scope from the back FAILED because "
//								"no elements are present\n");
			throw cannot_pop_out_of_empty_exception();
		}
//		if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//			LOG_F (INFO, "Popping last scope from the back\n");

		m_scopes.pop_back();
	}

	expression
	parsing_context::define_identifier(const identifier& ident)
	{
//		if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//			LOG_S (INFO) << "Defining identifier \"" << ident.name() << "\"";

		bool is_duplicate = std::any_of(scopes().begin(), scopes().end(), [&](const identifier& s)
		{
		  return s == ident;
		});

		if (is_duplicate)
		{
//			if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//				LOG_S (WARNING) << "Duplicate definition of \"" + ident.name() << "\".";
			throw kp::syntax_error(yy_location, "Duplicate definition of \"" + ident.name() + "\".");
		}

		scopes_mut().push_back(ident);

		return expression(ident);
	}

	expression
	parsing_context::use_identifier(const std::string& name) const
	{
//		if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//			LOG_S (INFO) << "Using identifier \"" + name << "\".";

		auto it = std::find_if(scopes().begin(), scopes().end(),
			[&](const auto& s)
			{ return s.name() == name; });

		if (it != scopes().end())
		{
			return expression(*it);
		}

//		if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//			LOG_S (WARNING) << "Unknown identifier \"" + name << "\".";
		throw kp::syntax_error(yy_location,
			"Unknown identifier \"" + name + "\"");
	}

	const function&
	parsing_context::define_function_body(const std::string& name,
		expression&& body)
	{
		/// Adds implicit return statement at the end of the block
		/// "concatenated" by this double-compound statement
		auto new_body = sa::compound_stmt({
			body,
			return_stmt()
		});

		m_current_function.set_body(move(new_body));
		m_current_function.set_name(name);

//		if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//			LOG_S (INFO) << "Defining function (\"" + name << "\") with body.\n";
		m_functions.push_back(m_current_function);
		m_current_function = {};
		return m_functions.back();
	}

	expression
	parsing_context::define_local(std::string&& name)
	{
//		if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//			LOG_S (INFO) << "Defining local variable (\"" + name << "\")" << '\n';
		return define_identifier(identifier(identifier::type::Local, move(name),
			m_current_function.add_local()));
	}

	expression
	parsing_context::define_function(std::string name)
	{
//		if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//			LOG_S (INFO) << "Defining function (\"" + name << "\")" << '\n';
		return define_identifier(identifier(identifier::type::Function,
			move(name), functions().size()));
	}

	expression
	parsing_context::define_parameter(std::string&& name)
	{
//		if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//			LOG_S (INFO) << "Defining parameter (\"" + name << "\")" << '\n';
		return define_identifier(identifier(identifier::type::Parameter,
			move(name),
			m_current_function.add_param()));
	}

	expression
	parsing_context::define_register()
	{
		std::string name = "$L" + std::to_string(m_registers++);
//		if (cli::globals.verbosity_level == cli::settings::verbosity::v2)
//			LOG_S (INFO) << "Defining register (\"" + name << "\")" << '\n';
		return define_local(move(name));
	}

	bool
	operator==(const identifier& This, const identifier& other)
	{
		return (This.name() == other.name()
			&& This.get_type() == other.get_type());
	}
}


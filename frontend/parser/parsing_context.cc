#include <algorithm>

#define LOGURU_WITH_STREAMS 1
#include <loguru/loguru.hpp>
//#include <util/common.hh>

#include "parser.tab.hh"
#include "parsing_context.hh"
#include "expressions.hh"
#include "statements.hh"
#include "syntax.hh"

/**
 * @file parsing_context.cc
 * @brief Implements the API of the `parsing_context` class.
 */

using kp = yy::kivi_parser;

using std::move;

namespace syntax_analyzer
{
	parsing_context::parsing_context(const char* code_beginning, std::string* filename)
		: lexer_cursor(code_beginning)
	{
		yy_location.begin.filename = filename;
		yy_location.end.filename = filename;
		LOG_F (INFO, "Initializing parsing_context\n");
	}

	void
	parsing_context::enter_scope()
	{
		LOG_F (INFO, "Placing a new scope at the end\n");
		m_all_scopes.emplace_back();
	}

	void
	parsing_context::exit_scope()
	{
		if (m_all_scopes.empty())
		{
			LOG_F (WARNING, "Popping last scope from the back FAILED because no elements are present\n");
			throw cannot_pop_out_of_empty_exception();
		}
		LOG_F (INFO, "Popping last scope from the back\n");
		m_all_scopes.pop_back();
	}

	expression
	parsing_context::define_identifier(const identifier& ident)
	{
//		const std::string& name = ident.name();
//		LOG_S (INFO) << "Defining identifier \"" << name << "\"";
//
//		bool is_duplicate = std::any_of(all_scopes().begin(), all_scopes().end(), [&](const auto& s)
//		{
//		  return s.name() == name;
//		});
//
//		if (is_duplicate)
//		{
//			LOG_S (WARNING) << "Duplicate definition of \"" + ident.name() << "\".";
//			throw kp::syntax_error(yy_location, "Duplicate definition of \"" + ident.name() + "\".");
//		}
//
//		all_scopes_mut().push_back(ident);
//
//		// Return the just pushed identifier
//		return all_scopes().back();
		return expression();
	}

	expression
	parsing_context::use_identifier(const std::string& name) const
	{
		LOG_S (INFO) << "Using identifier \"" + name << "\".";

		auto it = std::find_if(all_scopes().begin(), all_scopes().end(), [&](const auto& s)
		{
		  return s.name() == name;
		});

		if (it != all_scopes().end())
		{
			return expression(*it);
		}

		LOG_S (WARNING) << "Unknown identifier \"" + name << "\".";
		throw kp::syntax_error(yy_location, "Unknown identifier \"" + name + "\"");
	}

	const function&
	parsing_context::define_function_body(std::string&& name,
		expression&& body)
	{
		/// Adds implicit return statement at the end of the block
		/// "concatenated" by this double-compound statement
		expression fun_body{ move(body) };
		fun_body.merge_with(move(return_stmt()));

		LOG_S (INFO) << "Defining function (\"" + name << "\") with body.\n";
		m_all_functions.emplace_back(move(name), move(fun_body));
		return m_all_functions.back();
	}

	expression
	parsing_context::define_local(std::string&& name)
	{
		LOG_S (INFO) << "Defining local variable (\"" + name << "\")" << '\n';
		return define_identifier(identifier(identifier::type::Local, move(name), m_this_function.add_local()));
	}

	expression
	parsing_context::define_function(std::string&& name)
	{
		LOG_S (INFO) << "Defining function (\"" + name << "\")" << '\n';
		return define_identifier(identifier(identifier::type::Function, move(name), all_functions().size()));
	}

	expression
	parsing_context::define_parameter(std::string&& name)
	{
		LOG_S (INFO) << "Defining parameter (\"" + name << "\")" << '\n';
		return define_identifier(identifier(identifier::type::Parameter, move(name), m_this_function.add_param()));
	}

	expression
	parsing_context::define_register()
	{
		std::string name = "$L" + std::to_string(m_registers++);
		LOG_S (INFO) << "Defining register (\"" + name << "\")" << '\n';
		return define_local(move(name));
	}

	bool
	operator==(const identifier& This, const identifier& other)
	{
		return (This.name() == other.name() && This.get_type() == other.get_type());
	}

}

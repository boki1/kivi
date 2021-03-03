#include "include/parser.hpp"
#include "include/kivi_parser.tab.hh"
#include <algorithm>


const identifier &
parsing_context::define_identifier (const std::string &name, identifier &&f)
{
    auto it = m_scope_list.back().emplace(name, std::move(f));
    if (!it.second) {
		throw yy::kivi_parser::syntax_error (location, "Duplicate definition <" + name + ">");
    }
    return it.first->second;
}

expression
parsing_context::use_identifier (const std::string &name) const
{
    for (auto j = m_scope_list.crbegin (); j != m_scope_list.crend (); ++j) {
        if (auto i = j->find (name); i != j->end ()) {
            return expression (i->second);
        }
    }

	throw yy::kivi_parser::syntax_error (location, "Undefined identifier <" + name + ">");

}

void
parsing_context::add_function_with_block (std::string &&name,
					  expression &&code)
{
    // Add implicit return 0; at the end
    m_current_function.code
	= new_expression_sequence_expr (std::move (code), new_retrn_expr (1ul));
    m_current_function.name = std::move (name);
    m_function_list.push_back (std::move (m_current_function));
    m_current_function = {};
}

expression
parsing_context::define_local (const std::string &name)
{
    return define_identifier (
	name, identifier{ identifier_type::LOCAL,
			  m_current_function.num_locals++, name });
}

expression
parsing_context::define_function (const std::string &name)
{
    return
	define_identifier (name, identifier{ identifier_type::FUNCTION,
					     m_function_list.size (), name });
}
expression
parsing_context::define_parameter (const std::string &name)
{
    return define_identifier (
	name, identifier{ identifier_type::PARAMETER,
			  m_current_function.num_parameters++, name });
}
expression
parsing_context::new_register_variable ()
{
    return expression (
	define_local ("$I" + std::to_string (m_register_counter++)));
}

void
parsing_context::enter_scope ()
{
    m_scope_list.emplace_back ();
}

void
parsing_context::exit_scope ()
{
    m_scope_list.pop_back ();
}

void expression::splice_parameter_list_with(expression &&other)
{
    m_parameters.splice(m_parameters.end(), std::move(other.m_parameters));
}

/**
 * @file syntax.cc
 * @brief Provides implementation for the syntax header
 */

#include <string>
#include <utility>

#include "syntax.hh"

namespace sa = syntax_analyzer;

using std::move;

namespace syntax_analyzer
{
	//
	// Expression
	//

	expression::expression(sa::identifier&& ident)
		: m_terminal_value{ ident },
		  m_type{ expression::type::Identifier },
		  m_peculiar{}
	{
	}

	expression::expression(const identifier& ident)
		: m_terminal_value{ ident },
		  m_type{ expression::type::Identifier },
		  m_peculiar{}
	{
	}

	expression::expression(std::string&& str)
		: m_terminal_value{ str },
		  m_type{ expression::type::String },
		  m_peculiar{}
	{
	}

	expression::expression(int num)
		: m_terminal_value{ num },
		  m_type{ expression::type::Number },
		  m_peculiar{}
	{
	}

	expression expression::assign(expression&& rhs)&&
	{
		return expression(expression::type::Copy, { move(rhs), move(*this) });
	}

	void expression::append(expression&& appendant)
	{
		m_operands.push_back(move(appendant));
	}

	void expression::merge_with(expression&& other)
	{
		m_operands.insert(m_operands.end(), other.m_operands.begin(), other.m_operands.end());
	}

	expression::expression(expression::type type, std::vector<expression> operands)
		: m_type{ type },
		  m_operands(move(operands)),
		  m_peculiar{}
	{
	}

	expression::expression(expression::type type, expression::peculiar_type&& peculiar, std::vector<expression> operands)
		: m_type{ type },
		  m_peculiar{ move(peculiar) },
		  m_operands{ move(operands) }
	{
	}


	//
	// Function
	//

	function::function(std::string&& name, expression&& body, int locals, int parameters)
		: m_body(move(body)),
		  m_name(move(name)),
		  m_locals(locals),
		  m_parameters(parameters)
	{
	}

	//
	// Identifier
	//

	identifier::identifier(identifier::type type, std::string&& name, int index)
		: m_name{ std::move(name) },
		  m_type{ type },
		  m_index_within{ index }
	{
	}

}
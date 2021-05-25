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
		: m_terminal_value{ ident }, m_type{ expression::type::Identifier }
	{
	}

	expression::expression(const identifier& ident)
		: m_terminal_value{ ident }, m_type{ expression::type::Identifier }
	{
	}

	expression::expression(std::string&& str)
		: m_terminal_value{ str }, m_type{ expression::type::String }
	{
	}

	expression::expression(int num)
		: m_terminal_value{ num }, m_type{ expression::type::Number }
	{
	}

	expression
	expression::assign(expression&& rhs)&&
	{
		return expression(expression::type::Copy, { move(rhs), move(*this) });
	}

	void
	expression::front_add(expression&& to_add)
	{
		m_operands.insert(m_operands.begin(), move(to_add));
	}

	void
	expression::add(expression&& to_add)
	{
		m_operands.push_back(move(to_add));
	}

	void
	expression::extend(expression&& other)
	{
		m_operands.insert(m_operands.end(), other.m_operands.begin(),
			other.m_operands.end());
	}

	expression::expression(expression::type type,
		std::vector<expression> operands)
		: m_type{ type }, m_operands(move(operands))
	{
	}

	bool
	expression::operator==(const expression& other) const noexcept
	{
		if (get_type() != other.get_type())
			return false;

		if (operands().size() != other.operands().size())
			return false;

		auto it_this = operands().begin();
		auto it_other = other.operands().begin();
		while (
			it_this
				!= operands().end()) // We already know that they the have same size
		{
			if (*it_this != *it_other)
				return false;
			it_this++, it_other++;
		}
		if (!(terminal() == other.terminal()))
			return false;

		return true;
	}

	bool
	expression::operator!=(const expression& other) const noexcept
	{
		return !(*this == other);
	}

//
// Function
//

	function::function(std::string&& name, expression&& body, int locals,
		int parameters)
		: m_body(move(body)), m_name(move(name)), m_locals(locals),
		  m_parameters(parameters)
	{
	}

	bool
	function::operator==(const function& other) const
	{
		return parameters() == other.parameters() && locals() == other.locals()
			&& body() == other.body() && name() == other.name();
	}

//
// Identifier
//

	identifier::identifier(identifier::type type, std::string&& name, int index)
		: m_name{ std::move(name) }, m_type{ type }, m_index_within{ index }
	{
	}

}

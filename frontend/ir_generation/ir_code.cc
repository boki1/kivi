#include "ir_code.hh"

namespace intermediate_representation
{

	tac::tac(const std::string& str, int value, const operands_type& operands) : tac{ type::Init, operands, value, str }
	{
	}

	tac::tac(const tac_ptr& branch, const operands_type& operands)
		: m_condition(branch), m_operands(operands), m_type(type::IfNotZero)
	{
	}

	tac::tac(tac::type tac_type,
		const tac::operands_type& operands /* = {} */ ,
		int value /* = 0 */,
		const std::string& i /* = {} */,
		const tac::tac_ptr& next /* = { nullptr } */,
		const std::optional<tac_ptr>& condition /* = {} */)

		: m_value{ value }, m_identifier{ i }, m_next{ next }, m_condition{ condition }, m_operands{ operands }, m_type{ tac_type }
	{
	}

	tac::tac(const std::vector<vregister_type>& operands) : tac{ type::Nop, operands }
	{
	}

	tac::tac(const std::string& i, const operands_type& operands) : m_identifier(), m_operands(operands)
	{
	}
}



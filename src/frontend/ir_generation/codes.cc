/**
 * @file codes.cc
 * @brief Defines the "constructors" for all concrete TAC's
 */

#include "generation_unit.hh"
#include "ir_code.hh"

//!
//! `tac` stands for Three-Address Code
//!

namespace ir = intermediate_representation;
using opers_type = ir::tac::operands_type;
using gu = ir::generation_unit;
using tac_type = ir::tac::type;

namespace intermediate_representation
{
	tac* gu::tac_nop()
	{
		return define_tac(tac{ tac_type::Nop });
	}

	tac* gu::tac_init(unsigned int value, const std::string& ident,
		unsigned operand)
	{
		return define_tac(
			tac{ tac_type::Init, { operand }, static_cast<int>(value), ident });
	}

	tac* gu::tac_add(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Add, operands });
	}

	tac* gu::tac_neg(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Negate, operands });
	}

	tac* gu::tac_mult(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Multiplication, operands });
	}

	tac* gu::tac_div(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Division, operands });
	}

	tac* gu::tac_mod(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Modulo, operands });
	}

	tac* gu::tac_copy(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Copy, operands });
	}

	tac* gu::tac_eq(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Equals, operands });
	}

	tac* gu::tac_ifnz(const opers_type& operands)
	{
		auto code = define_tac(tac{ tac_type::IfNotZero, operands });
		code->set_has_condition();
		return code;
	}

	tac* gu::tac_fcall(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::FunctionCall, operands });
	}

	tac* gu::tac_return(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Return, operands });
	}

	tac* gu::tac_goto(const std::string& branch_label)
	{
		return define_tac(tac{ branch_label });
	}

} // namespace intermediate_representation
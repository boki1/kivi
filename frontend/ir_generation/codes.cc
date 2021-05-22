/**
 * @file codes.cc
 * @brief Defines the "constructors" for all concrete TAC's
 */

#include "ir_code.hh"
#include "generation_unit.hh"

//!
//! `tac` stands for Three-Address Code
//!

namespace ir = intermediate_representation;
using opers_type = ir::tac::operands_type;
using gu = ir::generation_unit;
using tac_type = ir::tac::type;

namespace intermediate_representation
{
	tac*
	gu::tac_nop()
	{
		return define_tac(tac{ tac_type::Nop });
	}

	tac*
	gu::tac_init(unsigned int value, const std::string& ident, unsigned operand)
	{
		return define_tac(tac{ tac_type::Init, { operand }, static_cast<int>(value), ident });
	}

	tac*
	gu::tac_add(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Add, operands });

	}

	tac*
	gu::tac_neg(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Negate, operands });

	}

	tac*
	gu::tac_copy(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Copy, operands });

	}

	tac*
	gu::tac_read(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Read, operands });

	}

	tac*
	gu::tac_write(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Write, operands });

	}

	tac*
	gu::tac_eq(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Equals, operands });

	}

	tac*
	gu::tac_ifnz(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::IfNotZero });

	}

	tac*
	gu::tac_fcall(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::FunctionCall, operands });

	}

	tac*
	gu::tac_return(const opers_type& operands)
	{
		return define_tac(tac{ tac_type::Return, operands });

	}

}
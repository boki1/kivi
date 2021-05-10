/**
 * @file syntactic_structure.cc
 * @brief Implements the syntactic_structure methods
 */

#include <util/common.hh>

#include "syntactic_structure.hh"

using sa_value = syntax_analyzer::I_evaluable_syntactic_structure;

sa_value::operator int() const noexcept
{
	Unimplemented();
	return 0;
}

int sa_value::operator-(const value& rhs) const noexcept
{
	Unimplemented();
	return 0;
}

bool sa_value::operator==(int rhs) const noexcept
{
	Unimplemented();
	return false;
}

bool sa_value::operator==(const value& rhs) const noexcept
{
	int rhs_as_int = static_cast<int>(rhs);
	return *this == rhs_as_int;
}








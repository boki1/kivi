/**
 * @file x86_64_instruction_selection.test.cc
 * @brief Tests the instruction selection phase of the x86_64 backend
 */
#include <exception>
#include <catch2/catch2.hpp>

#include <ir_generation/ir_code.hh>
#include <compiler/emitter.hh>
#include <arch/all.hh>
#include <arch/x86_64/x86_64_machine_target.hh>

namespace ir = intermediate_representation;
using TAC_type = ir::tac::type;

SCENARIO("Perform instruction selection", "[x86_64_iselect]")
{
	GIVEN("Sequence of three address code statements")
	{
		std::vector<ir::tac> mapped_TACs{
			ir::tac{ TAC_type::Init, { 0 }, static_cast<int>(1), "" },
			ir::tac{ TAC_type::Init, { 1 }, static_cast<int>(2), "" },
			ir::tac{ TAC_type::Equals, { 0, 1 }},
			ir::tac{ TAC_type::Init, { 2 }, static_cast<int>(3), "" },
			ir::tac{ TAC_type::Copy, { 1, 2 }},
		};

		std::vector<ir::tac> maybe_unmapped_TACs{
			ir::tac{ TAC_type::Init, { 2 }, static_cast<int>(3), "" },
			ir::tac{ TAC_type::Copy, { 1, 2 }},
			ir::tac{ TAC_type::Add, { 9, 1 }},
			ir::tac{ TAC_type::Return, { 9 }},
		};

		WHEN("All tac types are legal and appear in the x86_64 mapping to KIVI IR")
		{
			auto x64_emitter = compiler::emitter{ compiler::configure_target<compiler::x86_64>(), mapped_TACs };

			THEN("Each of the TACs gets associated to an x86_64 instruction or a sequence of such")
			{
				bool is_ok = x64_emitter.select_instructions();
				REQUIRE(is_ok);
			}
		}

		WHEN("Some of the TACs' types are not legal or not appear in the x86_64 mapping to KIVI IR")
		{
			auto x64_emitter = compiler::emitter{ compiler::configure_target<compiler::x86_64>(), maybe_unmapped_TACs };

			THEN("The instruction selection fails and reports the failure")
			{
				bool is_ok = x64_emitter.select_instructions();
				REQUIRE(!is_ok);
			}
		}
	}
}

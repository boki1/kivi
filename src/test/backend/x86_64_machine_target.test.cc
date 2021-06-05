/**
 * @file x86_64_machine_target.test.cc
 * @brief Tests the construction of a n x86_64 machine target structure
 */
#include <exception>
#include <catch2/catch2.hpp>

#include <ir_generation/ir_code.hh>
#include <compiler/emitter.hh>
#include <arch/all.hh>
#include <arch/x86_64/x86_64_machine_target.hh>

namespace ir = intermediate_representation;

SCENARIO("Creating preconfigured x86_64 machine target emitter", "[x86_64-config]")
{
	GIVEN("A vector with multiple \"empty\" three-address-code statements")
	{
		std::vector<ir::tac> three_address_code{ 10, ir::tac{}};
		REQUIRE(three_address_code.size() > 1);

		WHEN ("Placing the three-address-code statements collection")
		{
			auto x64_emitter = compiler::emitter{ compiler::configure_target<compiler::x86_64>(), three_address_code };
			const auto& x64_target = x64_emitter.strategy();
			THEN ("The address code is passed to the machine target processing function")
			{
				REQUIRE(x64_emitter.output_file() == "a.asm");
				REQUIRE(x64_emitter.three_address_code().size() == three_address_code.size());
				REQUIRE(x64_emitter.program().empty());
				REQUIRE(x64_target.instruction_set().size() == 0);
				REQUIRE(x64_target.register_set().size() == 0);
				REQUIRE(x64_target.stk_alloc_fptr());
				REQUIRE(x64_target.stk_dealloc_fptr());

			}
		}
	}
}
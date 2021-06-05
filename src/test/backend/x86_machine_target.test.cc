/**
 * @file example_test.cc
 * @brief Demonstrates an example usage of the catch2 testing framework
 */

#include <exception>

#include <catch2/catch2.hpp>
#include <ir_generation/ir_code.hh>
#include <compiler/emitter.hh>
#include <arch/all.hh>
#include <arch/x86/x86_machine_target.hh>

namespace ir = intermediate_representation;

SCENARIO("Creating preconfigured x86 machine target emitter", "[x86-config]")
{
	GIVEN("A vector with multiple \"empty\" three-address-code statements")
	{
		std::vector<ir::tac> three_address_code{ 10, ir::tac{}};
		REQUIRE(three_address_code.size() > 1);

		WHEN ("Placing the three-address-code statements collection")
		{
			auto x86_emitter = compiler::emitter{ compiler::configure_target<compiler::x86>(), three_address_code };
			const auto& x86_target = x86_emitter.strategy();
			THEN ("The address code is passed to the machine target processing function")
			{
				REQUIRE(x86_emitter.output_file() == "a.asm");
				REQUIRE(x86_emitter.three_address_code().size() == three_address_code.size());
				REQUIRE(x86_emitter.program().empty());
				REQUIRE(x86_target.instruction_set().size() == 0);
				REQUIRE(x86_target.register_set().size() == 0);
				REQUIRE(x86_target.stk_alloc_fptr());
				REQUIRE(x86_target.stk_dealloc_fptr());

			}
		}
	}
}
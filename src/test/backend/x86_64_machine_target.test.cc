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

		WHEN ("The address code is passed to the machine target processing function")
		{
            auto x64_emitter = compiler::emitter{ compiler::configure_target<compiler::x86_64>(), three_address_code };
            const auto& x64_target = x64_emitter.strategy();

            THEN ("Size is as expected")
			{
                REQUIRE(x64_emitter.three_address_code().size() == three_address_code.size());
			} AND_THEN("Emitter program is empty") {
				REQUIRE(x64_emitter.program().empty());
			} AND_THEN("Target instruction set is empty") {
				REQUIRE(x64_target.instruction_set().empty());
			} AND_THEN("Target register set is empty") {
				REQUIRE(x64_target.register_set() == compiler::x86_machine_target::x86_regs);
			} AND_THEN("Target stack pointer is allocated") {
				REQUIRE(x64_target.stk_alloc_fptr());
			} AND_THEN("Deallocated target stack pointer is bigger than the allocated one") {
				REQUIRE(x64_target.stk_dealloc_fptr() > x64_target.stk_alloc_fptr());
			}
		}

	}
}
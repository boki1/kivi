#ifndef KIVI_SRC_BACKEND_ARCH_X86_X86_MACHINE_TARGET_HH_
#define KIVI_SRC_BACKEND_ARCH_X86_X86_MACHINE_TARGET_HH_

#include <compiler/machine_target.hh>
#include <arch/all.hh>

namespace compiler
{
	namespace x86_machine_target
	{

		static const machine_target::instruction_set_type x86_is{};
		static const machine_target::register_set_type x86_regs{};
		static const std::unordered_map<ir::tac::type, instruction> x86_mappings{

		};

		template<typename T>
		[[nodiscard]] word<T> stkmem_allocate(int bytes)
		{
			return word<unsigned>{ 10 };
		}

		template<typename T>
		[[nodiscard]] word<T> stkmem_deallocate(int bytes)
		{
			return word<unsigned>{ 10 };
		}
	}

	/**
	 * @brief Setup an x86 target machine
	 * @return The resulting machine target
	 */
	template<>
	[[nodiscard]] machine_target configure_target<x86>()
	{
		using namespace x86_machine_target;
		return machine_target{ x86_is, x86_regs, x86_mappings, stkmem_allocate, stkmem_deallocate };
	}
}
#endif //KIVI_SRC_BACKEND_ARCH_X86_X86_MACHINE_TARGET_HH_

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

		[[nodiscard]] bool stkmem_allocate(int bytes)
		{
			return false;
		}

		[[nodiscard]] bool stkmem_deallocate(int bytes)
		{
			return false;
		}
	}

	template<>
	[[nodiscard]] machine_target default_target<x86>()
	{
//		return machine_target{};
	}
}
#endif //KIVI_SRC_BACKEND_ARCH_X86_X86_MACHINE_TARGET_HH_

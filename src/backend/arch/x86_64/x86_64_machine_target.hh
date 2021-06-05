#ifndef KIVI_SRC_BACKEND_ARCH_X86_X86_MACHINE_TARGET_HH_
#define KIVI_SRC_BACKEND_ARCH_X86_X86_MACHINE_TARGET_HH_

#include <compiler/machine_target.hh>
#include <arch/all.hh>

using TAC = ir::tac::type;

namespace compiler
{
	namespace x86_machine_target
	{

		static const machine_target::instruction_set_type x86_is{};
		static const machine_target::register_set_type x86_regs{};

		//! TODO:
		//! In order to provide minimal amount of optimization during the instruction selection stage, add an additional
		//! "rule" which is responsible for checking whether a lighter instruction may be used (e.g. when adding 1, prefer inc over add).

		static const std::unordered_map<ir::tac::type, std::vector<instruction>> x86_mappings{
			{ TAC::Nop, {{ "nop" }}},
			{ TAC::Init, {{ "mov", 2 }}},
			{ TAC::Equals, {{ "cmp", 2 }}},
			{ TAC::Copy, {{ "mov", 2 }}}
		};

		template<typename T>
		[[nodiscard]] word<T> stkmem_allocate(int bytes)
		{
			return word<uint64_t>{ 10 };
		}

		template<typename T>
		[[nodiscard]] word<T> stkmem_deallocate(int bytes)
		{
			return word<uint64_t>{ 10 };
		}
	}

	/**
	 * @brief Setup an x86_64 target machine
	 * @return The resulting machine target
	 */
	template<>
	[[nodiscard]] machine_target configure_target<x86_64>()
	{
		using namespace x86_machine_target;
		return machine_target{ x86_is, x86_regs, x86_mappings, stkmem_allocate, stkmem_deallocate };
	}
}
#endif //KIVI_SRC_BACKEND_ARCH_X86_X86_MACHINE_TARGET_HH_

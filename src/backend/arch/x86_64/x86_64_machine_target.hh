#ifndef KIVI_SRC_BACKEND_ARCH_X86_X86_MACHINE_TARGET_HH_
#define KIVI_SRC_BACKEND_ARCH_X86_X86_MACHINE_TARGET_HH_

#include <compiler/machine_target.hh>
#include <arch/all.hh>
#include <ir_generation/generation_context.hh>

using TAC_type = ir::tac::type;

namespace compiler
{
	namespace x86_machine_target
	{

		static const machine_target::instruction_set_type x86_is{};
		static const machine_target::register_set_type x86_regs{};

		//! TODO:
		//! In order to provide minimal amount of optimization during the instruction selection stage, add an additional
		//! "rule" which is responsible for checking whether a lighter instruction may be used (e.g. when adding 1, prefer inc over add).

		std::vector<instruction> x86_map(const ir::tac& TAC)
		{
			std::vector<instruction> result;
			result.reserve(1);

			auto TAC_gencontext = ir::generation_unit::generation_context::create_dont_reserve();
			auto new_vreg = [&TAC_gencontext]() -> ir::tac::vregister_type
			{ return TAC_gencontext.increase_counter(); };

			switch (TAC.get_type())
			{

			case TAC_type::Nop:
				result.emplace_back("nop");
				break;

			case TAC_type::Equals:
				result.emplace_back("cmp", 2, std::vector{ TAC.operands()[0], TAC.operands()[1] });
				break;

			case TAC_type::Negate:
				result.emplace_back("mov", 2, std::vector{ TAC.operands()[0], TAC.operands()[1] });
				result.emplace_back("neg", 1, std::vector{ TAC.operands()[0] });
				break;

			case TAC_type::Return:
				result.emplace_back("ret", 0, TAC.operands());

			case TAC_type::Add:
				/// TAC: add R0, R1, R2
				/// Meaning: R0 = R1 + R2
				///----------------------
				/// x86_64: mov R0, R2
				///			add R0, R1
				/// Meaning: Store R2 in R0
				///			 Add R1 to R0
				result.emplace_back("mov", 2, std::vector{ TAC.operands()[0], TAC.operands()[2] });
				result.emplace_back("add", 2, std::vector{ TAC.operands()[0], TAC.operands()[1] });
				break;

				//! Note for multiplication, division and modular division
				//! All of their associated instructions expect to be passed only the multiplier (or the divider respectively)
				//! The initial value of the operation is always stored in %eax and the result is put back into %eax (in the case
				//! of modulo division, the actual remainder is stored into %eax.
				//!
				//! The overall look of these operations is the following:
				//! mov Rnew, R1
				//! mul/div R2
				//! mov R0, Rnew
				//! where Rnew is precolored as %eax and stores its value before the start of the operation and loads it
				//! again at the end
			case TAC_type::Multiplication:
			{
				auto Reax = new_vreg();
				result.emplace_back("mov", 2, std::vector{ Reax, TAC.operands()[1] });
				result.back().precolor(Reax, "%eax");
				result.emplace_back("imul", 2, std::vector{ TAC.operands()[2] });
				result.emplace_back("mov", 2, std::vector{ TAC.operands()[0], Reax });
				result.back().precolor(Reax, "%eax");
			}
				break;

			case TAC_type::Division:
			{
				auto Reax = new_vreg();
				result.emplace_back("mov", 2, std::vector{ Reax, TAC.operands()[1] });
				result.back().precolor(Reax, "%eax");
				result.emplace_back("idiv", 2, std::vector{ TAC.operands()[2] });
				result.emplace_back("mov", 2, std::vector{ TAC.operands()[0], Reax });
				result.back().precolor(Reax, "%eax");
			}
				break;

			case TAC_type::Modulo:
			{
				auto Reax = new_vreg();
				auto Redx = new_vreg();
				result.emplace_back("mov", 2, std::vector{ Reax, TAC.operands()[1] });
				result.back().precolor(Reax, "%eax");
				result.emplace_back("idiv", 2, std::vector{ TAC.operands()[2] });
				result.emplace_back("mov", 2, std::vector{ TAC.operands()[0], Redx });
				result.back().precolor(Redx, "%edx");
			}

			case TAC_type::Copy:
				result.emplace_back("mov", 2, std::vector{ TAC.operands()[0], TAC.operands()[1] });
				break;

			case TAC_type::Init:
				// TODO: Handle function "initializations"
				result.emplace_back("mov", 2, std::vector{ TAC.operands()[0] });
				result.back().add_int_literal(TAC.value());
				break;

			case TAC_type::IfNotZero:
				result.emplace_back("cmp", 2, std::vector{ TAC.operands()[0] });
				result.back().add_int_literal(0);
				result.emplace_back("jnz", 2, std::vector{ TAC.operands()[0] });
				result.back().add_jmp_label(TAC.branching_label());
				break;

			case TAC_type::FunctionCall:
				result.emplace_back("fcall ...");
				break;

			case TAC_type::Goto:
				// Unreachable
				result.emplace_back("goto ...");
				break;
			}

			if (TAC.has_label())
				result.front().put_label(std::string{ TAC.label() }, TAC.is_function_label());

			return result;
		}

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
		return machine_target{ x86_is, x86_regs, x86_map, stkmem_allocate, stkmem_deallocate };
	}
}
#endif //KIVI_SRC_BACKEND_ARCH_X86_X86_MACHINE_TARGET_HH_

#ifndef KIVI_SRC_BACKEND_ARCH_X86_X86_MACHINE_TARGET_HH_
#define KIVI_SRC_BACKEND_ARCH_X86_X86_MACHINE_TARGET_HH_

#include <stack>
#include <cassert>

#include <compiler/machine_target.hh>
#include <arch/all.hh>
#include <ir_generation/generation_context.hh>

using TAC_type = ir::tac::type;
using Subreg_type = compiler::rregister::Subreg_type;

namespace compiler
{
	namespace x86_machine_target
	{

		// TODO: Is this actually required?
		static const machine_target::instruction_set_type x86_is{};

		static const machine_target::register_set_type x86_regs{

			//!
			//! Callee-owned
			//!

			rregister{ "rax", 8, true, false }, //< Return value
			rregister{ "eax", 4, true, false, "rax" },
			rregister{ "ax", 2, true, false, "eax", Subreg_type::Hi },
			rregister{ "al", 2, true, false, "eax", Subreg_type::Lo },
			rregister{ "rdi", 8, true, false }, //< First parameter
			rregister{ "edi", 4, true, false, "rdi" },
			rregister{ "dx", 2, true, false, "edi", Subreg_type::Hi },
			rregister{ "dl", 2, true, false, "edi", Subreg_type::Lo },
			rregister{ "rsi", 8, true, false }, //< Second parameter
			rregister{ "esi", 4, true, false, "rsi" },
			rregister{ "sx", 2, true, false, "esi", Subreg_type::Hi },
			rregister{ "sl", 2, true, false, "esi", Subreg_type::Lo },
			rregister{ "rdx", 8, true, false }, //< Third parameter
			rregister{ "edx", 4, true, false, "rdx" },
			rregister{ "dx", 2, true, false, "edx", Subreg_type::Hi },
			rregister{ "dl", 2, true, false, "edx", Subreg_type::Lo },
			rregister{ "rcx", 8, true, false }, //< Fourth parameter
			rregister{ "ecx", 4, true, false, "rcx" },
			rregister{ "cx", 2, true, false, "ecx", Subreg_type::Hi },
			rregister{ "cl", 2, true, false, "ecx", Subreg_type::Lo },
			rregister{ "r8", 8, true, false }, //< Fifth parameter
			rregister{ "r8d", 4, true, false, "r8" },
			rregister{ "r8w", 2, true, false, "r8d", Subreg_type::Hi },
			rregister{ "r8b", 2, true, false, "r8d", Subreg_type::Lo },
			rregister{ "r9", 8, true, false }, //< Fifth parameter
			rregister{ "r9d", 4, true, false, "r9" },
			rregister{ "r9w", 2, true, false, "r9d", Subreg_type::Hi },
			rregister{ "r9b", 2, true, false, "r9d", Subreg_type::Lo },
			rregister{ "r10", 8, true, false }, //< Scratch/temporary
			rregister{ "r10d", 4, true, false, "r10" },
			rregister{ "r10w", 2, true, false, "r10d", Subreg_type::Hi },
			rregister{ "r10b", 2, true, false, "r10d", Subreg_type::Lo },
			rregister{ "r11", 8, true, false }, //< Scratch/temporary
			rregister{ "r11d", 4, true, false, "r11" },
			rregister{ "r11w", 2, true, false, "r11d", Subreg_type::Hi },
			rregister{ "r11b", 2, true, false, "r11d", Subreg_type::Lo },

			//!
			//! Caller-owned
			//!

			{ "rsp", 8, false, true }, //< Stack pointer
			{ "esp", 4, false, true, "rsp" },
			{ "sp", 2, false, true, "esp", Subreg_type::Hi },
			{ "spl", 2, false, true, "esp", Subreg_type::Lo },
			{ "rbx", 8, false, true }, //< Local variable
			{ "ebx", 4, false, true, "rbx" },
			{ "bx", 2, false, true, "ebx", Subreg_type::Hi },
			{ "bl", 2, false, true, "ebx", Subreg_type::Lo },
			{ "rbp", 8, false, true }, //< Stack frame / Local variable
			{ "ebp", 4, false, true, "rbp" },
			{ "bp", 2, false, true, "ebp", Subreg_type::Hi },
			{ "bpl", 2, false, true, "ebp", Subreg_type::Lo },
			{ "r12", 8, false, true }, //< Local variable
			{ "r12d", 4, false, true, "r12" },
			{ "r12w", 2, false, true, "r12d", Subreg_type::Hi },
			{ "r12b", 2, false, true, "r12d", Subreg_type::Lo },
			{ "r13", 8, false, true }, //< Local variable
			{ "r13d", 4, false, true, "r13" },
			{ "r13w", 2, false, true, "r13d", Subreg_type::Hi },
			{ "r13b", 2, false, true, "r13d", Subreg_type::Lo },
			{ "r14", 8, false, true }, //< Local variable
			{ "r14d", 4, false, true, "r14" },
			{ "r14w", 2, false, true, "r14d", Subreg_type::Hi },
			{ "r14b", 2, false, true, "r14d", Subreg_type::Lo },
			{ "r15", 8, false, true }, //< Local variable
			{ "r15d", 4, false, true, "r15" },
			{ "r15w", 2, false, true, "r15d", Subreg_type::Hi },
			{ "r15b", 2, false, true, "r15d", Subreg_type::Lo },

			//!
			//! Special
			//!

			// Not added
		};

		// These two are exptected to be set when inserting the prologue of the callee and to be used by the epilogue as well
		// extern std::optional<ir::tac::vregister_type> Rrbp_opt;
		// extern std::optional<ir::tac::vregister_type> Rrsp_opt;

		std::optional<ir::tac::vregister_type> Rrbp_opt;
		std::optional<ir::tac::vregister_type> Rrsp_opt;

		//! TODO:
		//! In order to provide minimal amount of optimization during the instruction selection stage, add an additional
		//! "rule" which is responsible for checking whether a lighter instruction may be used (e.g. when adding 1, prefer inc over add).

		// std::vector<instruction> x86_map(const ir::tac& TAC, const std::unordered_map<ir::tac::vregister_type, std::string_view>& functions);


		std::vector<instruction> x86_map(
				const ir::tac& TAC,
				const std::unordered_map<ir::tac::vregister_type,
				std::string_view>& functions
			){
			std::vector<instruction> result;
			result.reserve(1);

			auto TAC_gencontext = ir::generation_unit::generation_context::create_dont_reserve();
			auto new_vreg = [&TAC_gencontext]() -> ir::tac::vregister_type
			{
			  return TAC_gencontext.increase_counter();
			};

			if (TAC.is_function_label()) //< Put function prologue
			{
				Rrbp_opt.reset();
				Rrsp_opt.reset();

				Rrbp_opt = std::make_optional(ir::tac::vregister_type{ new_vreg() });
				Rrsp_opt = std::make_optional(ir::tac::vregister_type{ new_vreg() });

				// We can safely call .value() since we just put value in it
				const auto& Rrbp = Rrbp_opt.value();
				const auto& Rrsp = Rrsp_opt.value();

				result.emplace_back("push", 1, std::vector{ Rrbp })
					.precolor(Rrbp, "rbp");
				result.emplace_back("mov", 2, std::vector{ Rrbp, Rrsp })
					.precolor(Rrbp, "rbp")
					.precolor(Rrsp, "rsp");
			}

			size_t current_register = 0ul;

			auto load_params =
				[&TAC_gencontext, &result, &new_vreg, &current_register](const auto& rev_start,
					const auto& rev_finish) mutable
				{
				  static std::array<std::string, 6> registers{ "rdi", "rsi", "rdx", "rcx", "r8", "r9" };
				  std::stack<std::pair<std::string, ir::tac::vregister_type>> stored;

				  // Push parameters in reverse order
				  for (auto it = rev_start; it != rev_finish; ++it)
				  {
					  ir::tac::vregister_type arg = *it;

					  if (current_register >= 6)
					  {
						  // TODO: From memory
						  result.emplace_back("mov", 2, std::vector{ ~0u, arg });
					  }
					  else
					  {
						  // push %reg
						  // mov %reg, paramN
						  auto Rnew = new_vreg();
						  const auto& carrier_reg = registers.at(current_register);
						  result.emplace_back("push", 1, std::vector{ Rnew }).precolor(Rnew, carrier_reg);
						  result.emplace_back("mov", 2, std::vector{ Rnew, arg }).precolor(Rnew, carrier_reg);
						  stored.push(std::make_pair(carrier_reg, Rnew));
					  }

					  current_register++;
				  }

				  return stored;
				};

			auto unload_params = [&](auto& occupied) -> void
			{
			  while (!occupied.empty())
			  {
				  auto &[reg, Rtemp] = occupied.top();
				  result.emplace_back("pop", 1, std::vector{ Rtemp }).precolor(Rtemp, reg);
				  occupied.pop();
			  }
			};

			switch (TAC.get_type())
			{

			case TAC_type::Nop:
				result.emplace_back("nop");
				break;

			case TAC_type::Equals:
			{
				result.emplace_back("cmp", 2, std::vector{ TAC.operands()[1], TAC.operands()[2] });
				result.emplace_back("mov", 2, std::vector{ TAC.operands()[0] }).add_int_literal(0);
				result.emplace_back("sete",
					1,
					std::vector{ TAC.operands()[0] }); //< [0] is a _byte_ register or memory
				break;
			}

			case TAC_type::Negate:
				result.emplace_back("mov", 2, std::vector{ TAC.operands()[0], TAC.operands()[1] });
				result.emplace_back("neg", 1, std::vector{ TAC.operands()[0] });
				break;

			case TAC_type::Return:
			{
				// If no prologue has been inserted -- don't know what to do
				assert(Rrbp_opt.has_value());
				assert(Rrsp_opt.has_value());
				const auto& Rrbp = Rrbp_opt.value();
				// Insert epilogue
				result.emplace_back("pop", 1, std::vector{ Rrbp }).precolor(Rrbp, "rbp");
				result.emplace_back("ret", 0, TAC.operands());
				break;
			}

			case TAC_type::Add:
				//! TAC: add R0, R1, R2
				//! Meaning: R0 = R1 + R2
				//!----------------------
				//! x86_64: mov R0, R2
				//!			add R0, R1
				//! Meaning: Store R2 in R0
				//!			 Add R1 to R0

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
				result.emplace_back("mov", 2, std::vector{ TAC.operands()[0] }).add_int_literal(TAC.value());
				break;

			case TAC_type::IfNotZero:
				result.emplace_back("cmp", 2, std::vector{ TAC.operands()[0] }).add_int_literal(0);
				result.emplace_back("jnz",
					2,
					std::vector{ TAC.operands()[0] }).add_jmp_label(TAC.branching_label());
				break;

			case TAC_type::FunctionCall:
			{
				/// There _are_ at least 2 operands in such statement:
				/// [0] := retval vreg container
				/// [1] := function name
				assert(TAC.operands().size() >= 2);

				std::stack<std::pair<std::string, ir::tac::vregister_type>>
					occupied = load_params(TAC.operands().rbegin(), TAC.operands().rend() - 1);

				const auto
					fun_label =
					std::string{ functions.at(TAC.operands()[1]) }; //< at(1) is the "function register"
				result.emplace_back("call").add_jmp_label(fun_label);

				// Cleanup and fetch retval
				auto& Rretval = TAC.operands()[0];
				auto Rrax = new_vreg();
				current_register = 0ul;
				result.emplace_back("mov", 2, std::vector{ Rretval, Rrax }).precolor(Rrax, "rax");

				unload_params(occupied);
				while (!occupied.empty())
				{
					auto &[reg, Rtemp] = occupied.top();
					result.emplace_back("pop", 1, std::vector{ Rtemp }).precolor(Rtemp, reg);
					occupied.pop();
				}

				break;
			}

			case TAC_type::Goto:
				result.emplace_back("jmp");
				result.back().add_jmp_label(TAC.branching_label());
				break;
			}

			if (TAC.has_label())
				result.front().put_label(TAC.label(), TAC.is_function_label());

			return result;
		}



		/// TODO:
		template<typename T>
		[[nodiscard]] word<T> stkmem_allocate(int bytes)
		{
			return word<uint64_t>{ 10 };
		}

		/// TODO:
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

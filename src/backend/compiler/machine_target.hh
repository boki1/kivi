#ifndef KIVI_MACHINE_TARGET_HH
#define KIVI_MACHINE_TARGET_HH

#include <string>
#include <utility>
#include <variant>
#include <vector>

#include <ir_generation/ir_code.hh>

#include "instruction_selector.hh"
#include "register_allocator.hh"
#include "common.hh"

namespace compiler
{
	class machine_target
	{
	 public:
		/// Template for the functions related to stack memory management
		/// @tparam	*unnamed*(bytes) The amount of bytes to be allocated
		/// @return The beginning of memory allocated
		/// @note In case of failure word{0} is returned
		/// @todo change word<T>
		using stackmem_management_fptr = word<uint32_t> (*)(int);

		using instruction_set_type = std::vector<instruction>;
		using register_set_type = std::vector<rregister>;

		machine_target(const instruction_set_type& t_is,
			const register_set_type& t_regs,
			const std::vector<ir::tac>& input,
			const std::unordered_map<ir::tac, instruction>& ir_to_native_mapping,
			stackmem_management_fptr alloc,
			stackmem_management_fptr drop
		)
			: m_instruction_set{ t_is },
			  m_registers{ t_regs },
			  m_allocate_stackmem_routine{ alloc },
			  m_free_stackmem_routine{ drop },
			  m_ir_input{ input },
			  m_instruction_selector{ input, ir_to_native_mapping },
			  m_register_allocator{}
		{
		}

	 private:

		/// _Used_ instruction set of the machine target
		const instruction_set_type& m_instruction_set;

		/// Registers of the target machine
		const register_set_type& m_registers;

		//!
		//! Stack memory management operations
		//!
		stackmem_management_fptr m_allocate_stackmem_routine{};
		stackmem_management_fptr m_free_stackmem_routine{};

		/// Concrete instruction selection algorithm
		instruction_selector m_instruction_selector;

		/// Concrete register allocation algorithm
		register_allocator m_register_allocator;

		/// The input program
		const std::vector<ir::tac>& m_ir_input;

	 public:

		template<typename T>
		[[nodiscard]] word<T> stk_alloc(int bytes)
		{
			return m_allocate_stackmem_routine(bytes);
		}

		template<typename T>
		[[nodiscard]] word<T> stk_free(int bytes)
		{
			return m_free_stackmem_routine(bytes);
		}

		const std::vector<instruction>& operator()()
		{
			return generate();
		}

		const std::vector<instruction>& generate()
		{
//			return ...
		}
	};
}

#endif //KIVI_MACHINE_TARGET_HH

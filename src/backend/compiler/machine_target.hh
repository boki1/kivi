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
		using stackmem_management_fptr = word<uint64_t> (*)(int);

		using instruction_set_type = std::vector<instruction>;
		using register_set_type = std::vector<rregister>;

		machine_target(const instruction_set_type& t_is,
			const register_set_type& t_regs,
			const std::unordered_map<ir::tac::type, std::vector<instruction>>& ir_to_native_mapping,
			stackmem_management_fptr alloc,
			stackmem_management_fptr drop
		)
			: m_instruction_set{ t_is },
			  m_registers{ t_regs },
			  m_allocate_stackmem_routine{ alloc },
			  m_free_stackmem_routine{ drop },
			  m_instruction_selector{ ir_to_native_mapping },
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

	 public:
		const std::vector<instruction>& process_input(const std::vector<ir::tac>& t_input)
		{
			/// DO STUFF
		}

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

	 public:
		[[nodiscard]] const instruction_set_type& instruction_set() const
		{
			return m_instruction_set;
		}
		[[nodiscard]] const register_set_type& register_set() const
		{
			return m_registers;
		}
		[[nodiscard]] instruction_selector& selector_mut()
		{
			return m_instruction_selector;
		}
		[[nodiscard]] const register_allocator& rallocator() const
		{
			return m_register_allocator;
		}
		[[nodiscard]] stackmem_management_fptr stk_alloc_fptr() const
		{
			return m_allocate_stackmem_routine;
		}
		[[nodiscard]] stackmem_management_fptr stk_dealloc_fptr() const
		{
			return m_free_stackmem_routine;
		}
	};
}

#endif //KIVI_MACHINE_TARGET_HH

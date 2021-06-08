#ifndef KIVI_INSTRUCTION_SELECTOR_HH
#define KIVI_INSTRUCTION_SELECTOR_HH

#include <unordered_map>
#include <vector>
#include <optional>

#include <ir_generation/ir_code.hh>

#include "common.hh"

namespace ir = intermediate_representation;

namespace compiler
{
	class instruction_selector
	{
	 private:
		/// TAC to machine target native instruction mapper
		TAC_to_native_mapper m_mapper;

		/// Instructions which are result from the selection
		std::vector<instruction> m_selected{};

		/// Function identifiers stored in registers in TAC form
		std::unordered_map<ir::tac::vregister_type, std::string_view> m_functions{};

	 public:
		explicit instruction_selector(TAC_to_native_mapper t_mapper)
			: m_mapper{ t_mapper }
		{
		}

	 public:
		/**
		 * @brief Performs a macro expansion instruction selection on the given collection of three address codes
		 * @param three_address_code
		 * @return true if successful and false if not
		 */
		void select_for(const std::vector<ir::tac>& TACs);

		/**
		 * @brief Acquire the result of the `select_for` call
		 * @return All selected instructions
		 */
		[[nodiscard]] auto
		fetch_selected_output() const
		{
			return std::make_pair(m_selected, m_functions);
		}
	};
}

#endif //KIVI_INSTRUCTION_SELECTOR_HH

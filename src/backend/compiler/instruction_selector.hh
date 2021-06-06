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
		const std::unordered_map<ir::tac::type, std::vector<instruction>>& m_mapping;
		std::vector<instruction> m_selected{};

	 public:
		explicit instruction_selector(const std::unordered_map<ir::tac::type, std::vector<instruction>>& t_mapping)
			: m_mapping{ t_mapping }
		{
		}

	 public:
		/**
		 * @brief Performs a macro expansion instruction selection on the given collection of three address codes
		 * @param three_address_code
		 * @return true if successful and false if not
		 */
		bool select_for(const std::vector<ir::tac>& TACs);

		/**
		 * @brief Performs a macro expansion instruction selection on a single three address code statement
		 * @param TAC The single IR statement
		 * @return The selected instruction
		 */
		bool select_for(const ir::tac& TAC);

		/**
		 * @brief Acquire the result of the `select_for` call
		 * @return All selected instructions
		 */
		const std::vector<instruction>& fetch_selected_output() const
		{
			return m_selected;
		}
	};
}

#endif //KIVI_INSTRUCTION_SELECTOR_HH

#ifndef KIVI_INSTRUCTION_SELECTOR_HH
#define KIVI_INSTRUCTION_SELECTOR_HH

#include <unordered_map>
#include <vector>

#include <ir_generation/ir_code.hh>

#include "common.hh"

namespace ir = intermediate_representation;

namespace compiler
{
	class instruction_selector
	{
	 private:
		const std::vector<ir::tac>& m_three_address_code;
		const std::unordered_map<ir::tac, instruction>& m_mapping;
		std::vector<instruction> m_selected{};

	 public:
		instruction_selector(const std::vector<ir::tac>& t_ir, const std::unordered_map<ir::tac, instruction>& t_mapping)
			: m_three_address_code{ t_ir },
			  m_mapping{ t_mapping }
		{
		}

	 public:
		bool operator()()
		{
			return false;
		}

		bool select()
		{
			return false;
		}

		const std::vector<instruction>& fetch_selected_output()
		{
			return m_selected;
		}
	};
}

#endif //KIVI_INSTRUCTION_SELECTOR_HH

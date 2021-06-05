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
		const std::unordered_map<ir::tac::type, instruction>& m_mapping;
		std::vector<instruction> m_selected{};

	 public:
		explicit instruction_selector(const std::unordered_map<ir::tac::type, instruction>& t_mapping)
			: m_mapping{ t_mapping }
		{
		}

	 public:
		bool operator()()
		{
			return false;
		}

		bool select_from(const std::vector<ir::tac>& three_address_code)
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

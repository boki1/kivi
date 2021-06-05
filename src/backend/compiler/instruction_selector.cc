#include <algorithm>
#include <optional>

#include "instruction_selector.hh"

namespace compiler
{
	bool instruction_selector::select_for(const ir::tac& TAC)
	{
		auto type = TAC.get_type();
		if (m_mapping.find(type) == m_mapping.end())
			return false;

		auto instructions = m_mapping.at(type);
		std::copy(instructions.begin(), instructions.end(), std::back_inserter(m_selected));
		return true;
	}

	bool instruction_selector::select_for(const std::vector<ir::tac>& TACs)
	{
		m_selected.clear();
		m_selected.reserve(TACs.size() + TACs.size() / 2);
		bool selection_failed = false;
		std::for_each(TACs.begin(), TACs.end(), [this, &selection_failed](const auto& TAC)
		{
		  selection_failed |= !select_for(TAC);
		});

		/// As of now, there is no way that the amount of input instruction could be bigger than the resulting
		/// instructions, so this is what we check to find whether the instruction_selector has selection_failed miserably.
		return !selection_failed && m_selected.size() <= TACs.size();
	}
}
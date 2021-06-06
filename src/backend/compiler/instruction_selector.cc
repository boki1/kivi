#include <algorithm>
#include <optional>

#include "instruction_selector.hh"

namespace compiler
{
	bool instruction_selector::select_for(const ir::tac& TAC)
	{
		auto instructions = m_mapper(TAC);
		std::copy(instructions.begin(), instructions.end(), std::back_inserter(m_selected));
		return true;
	}

	bool instruction_selector::select_for(const std::vector<ir::tac>& TACs)
	{
		m_selected.clear();
		m_selected.reserve(TACs.size() + TACs.size() / 2);

		return std::all_of(TACs.begin(), TACs.end(), [&](const ir::tac& TAC)
		{
		  return select_for(TAC);
		});
	}
}
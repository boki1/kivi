#include <algorithm>
#include <optional>
#include <unordered_map>

#include "instruction_selector.hh"

namespace compiler
{

	void instruction_selector::select_for(const std::vector<ir::tac>& TACs)
	{
		m_selected.clear();
		m_selected.reserve(TACs.size() + TACs.size() / 2);

		const auto function_identifiers = [&]() -> std::unordered_map<ir::tac::vregister_type, std::string_view>
		{
		  std::unordered_map<ir::tac::vregister_type, std::string_view> preprocessed;
		  std::for_each(TACs.begin(), TACs.end(), [&preprocessed](const ir::tac& TAC) mutable -> void
		  {
			if (TAC.get_type() == ir::tac::type::Init && !TAC.identifier().empty())
				preprocessed.emplace(TAC.operands()[0], TAC.identifier());
		  });
		  return preprocessed;
		}();

		std::for_each(TACs.begin(), TACs.end(), [&](const ir::tac& TAC)
		{
		  auto instructions = m_mapper(TAC, function_identifiers);
		  std::copy(instructions.begin(), instructions.end(), std::back_inserter(m_selected));
		});
	}
}
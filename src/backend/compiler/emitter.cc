#include "emitter.hh"

namespace compiler
{

	std::vector<emitter::basic_block> emitter::form_basic_blocks()
	{
		auto leaders = find_leaders();

		std::vector<basic_block> bblocks;
		bblocks.reserve(leaders.size() - 1);

		const auto program_begin = m_program.cbegin();
		for (auto it = m_program.cbegin(), begin = m_program.cbegin(), end = m_program.cbegin();
			 it != m_program.cend(); ++it)
		{
			if (it != leaders.front())
				continue;;

			end = it + 1; //< Place end over the end
			bblocks.emplace_back(begin, end, begin - program_begin, end - program_begin);
			begin = end;
			leaders.pop();
		}

		debug_meta.last_formed_blocks = bblocks;
		return bblocks;
	}

	std::queue<emitter::basic_block::stmt_ptr> emitter::find_leaders()
	{
		std::queue<basic_block::stmt_ptr> leaders;

		for (auto it = m_program.cbegin(), prev = m_program.cend(); it != m_program.cend(); prev = it, ++it)
		{
			// First program statement is a leader
			// If previous is a branch/jmp this is a leader
			// If this has a jump into it, it is a leader
			if ((it == m_program.cbegin())
				|| (prev->is_branch())
				|| (it->label.has_value()))
			{
				leaders.emplace(it);
			}

		}

		return leaders;
	}
}

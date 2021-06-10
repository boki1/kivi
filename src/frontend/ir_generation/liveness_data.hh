#ifndef KIVI_SRC_FRONTEND_IR_GENERATION_LIVENESS_DATA_HH
#define KIVI_SRC_FRONTEND_IR_GENERATION_LIVENESS_DATA_HH

#include <variant>
#include <algorithm>

#include "ir_code.hh"

namespace compiler
{
	// Forward declaration used in the liveness analyzer
	class unknown_vregister_exception;
}

class liveness_data
{
public:
	enum class Data_location_type
	{
		Memory,
		Register,
		Uninitialized
	};

	enum class Data_liveness_status
	{
		Alive,
		Dead
	};

	using data_location = std::variant<
		std::monostate, /* Data_location_type::Uninitialized */
		std::string_view, /* Data_location::Register */
		std::uintptr_t /* Data_location::Memory */
	>;

	using line_type = int;

	struct data_entry
	{
		/// Location of the data
		std::pair <Data_location_type, data_location> where;

		/// Last line where the data was alive
		line_type last_alive;

		/// Current status
		std::pair <line_type /* current line */, Data_liveness_status /* status */ > current_status;

		/// Live where entry was created
		line_type created_at;
	};

	using data_table_type = std::unordered_map<ir::tac::vregister_type, data_entry>;

private:
	/// Table containing meta information about data (where data is variable, or a temporary value inserted at compile-time)
	data_table_type m_table;

public:
	[[nodiscard]] auto table() -> const data_table_type&
	{
		return m_table;
	}
	[[nodiscard]] auto table_mut() -> data_table_type&
	{
		return m_table;
	}

	template<typename Location, typename ...Rest>
	auto put_entry(Location&& loc, Rest&& ... args) -> void
	{
		m_table.emplace_back(std::forward<Location>(loc), std::forward<Rest>(args)...);
	}

	void update_entry_liveness(ir::tac::vregister_type identifier, line_type current_line, Data_liveness_status status)
	{
		if (m_table.find(identifier) == m_table.end())
			throw compiler::unknown_vregister_exception{ identifier };

		m_table[identifier].current_status = std::make_pair(current_line, status);
	}

	auto move_entry_data(ir::tac::vregister_type identifier, Data_location_type loc_type, data_location loc)
	{
		if (m_table.find(identifier) == m_table.end())
			throw compiler::unknown_vregister_exception{ identifier };

		m_table[identifier].where = std::make_pair(loc_type, loc);
	}

};

#endif //KIVI_SRC_FRONTEND_IR_GENERATION_LIVENESS_DATA_HH

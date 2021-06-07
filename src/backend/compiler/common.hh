#ifndef KIVI_SRC_BACKEND_COMPILER_COMMON_HH_
#define KIVI_SRC_BACKEND_COMPILER_COMMON_HH_

#include <string_view>
#include <utility>
#include <variant>
#include <ostream>

#include <ir_generation/ir_code.hh>

namespace ir = intermediate_representation;

namespace compiler
{
	/// Forward declaration
	class instruction;

	using TAC_to_native_mapper = std::vector<instruction> (*)(const ir::tac&);

	/// Machine target register abstraction
	struct rregister
	{
		std::string_view name{};
		int bytes;
		bool is_callee_save;
		bool is_caller_save;

		constexpr rregister(const std::string_view& t_name, int t_bytes, bool t_callee = true, bool t_caller = true)
			: name{ t_name },
			  bytes{ t_bytes },
			  is_callee_save{ t_callee },
			  is_caller_save{ t_caller }
		{
		}
	};

	/// Machine target word abstraction
	template<typename T, std::enable_if_t<std::is_unsigned_v<T>, bool> = true>
	struct word
	{
		T ptr;
		constexpr explicit word(T t_ptr) : ptr{ t_ptr }
		{
		}
	};

	/// Machine target instruction abstraction
	struct instruction
	{
		/// The mnemonic of the instruction
		std::string_view name;

		/// Label if one is present and mark if it is a function or not
		std::optional<std::pair<std::string, bool>> label;

		/// Virtual expected_actual_operands
		std::vector<ir::tac::vregister_type> virtual_operands;

		/// Literal
		std::optional<int> int_literal{};

		/// Jump label
		std::optional<std::string_view> jmp_label{};

		/// Predefined virtual-actual register mappings
		std::unordered_map<ir::tac::vregister_type, std::string_view> precolored;

		/// Actual expected_actual_operands
		std::vector<std::string_view> actual_operands;

		/// The expected number of actual expected_actual_operands
		int expected_actual_operands;

		explicit instruction(const std::string_view& t_name,
			int t_operands = 0,
			const std::string& t_label = {},
			bool t_is_fun = false)
			: name{ t_name }, expected_actual_operands{ t_operands }, label{ std::make_pair(t_label, t_is_fun) }
		{
		}

		instruction(const std::string_view& t_name,
			int t_operands,
			std::vector<ir::tac::vregister_type> t_virtual_operands = {}
		)
			: name{ t_name }, expected_actual_operands{ t_operands }, virtual_operands{ std::move(t_virtual_operands) }
		{
		}

		void add_int_literal(int lit)
		{
			int_literal.emplace(lit);
		}
		void add_jmp_label(const std::string& t_label)
		{
			jmp_label.emplace(t_label);
		}

		bool precolor(ir::tac::vregister_type vregister, const std::string_view& color)
		{
			if (precolored.find(vregister) != precolored.end())
				return false;

			precolored.emplace(vregister, color);
		}

		void put_label(const std::string& t_label, bool t_is_fun)
		{
			auto new_label = std::make_optional(std::make_pair(t_label, t_is_fun));
			label.swap(new_label);
		}

		bool operator==(const instruction& rhs) const
		{
			return name == rhs.name && expected_actual_operands == rhs.expected_actual_operands;
		}

		friend std::ostream& operator<<(std::ostream& os, const instruction& instruction)
		{
			os << "{ name: " << instruction.name << ", expected_actual_operands: " << instruction.expected_actual_operands << "}";
			return os;
		}

		void add_virtual_operand(ir::tac::vregister_type voperand)
		{
			virtual_operands.push_back(voperand);
		}

		void add_actual_operand(std::string_view aoperand)
		{
			actual_operands.push_back(aoperand);
		}
	};
}

#endif //KIVI_SRC_BACKEND_COMPILER_COMMON_HH_

#ifndef KIVI_SRC_BACKEND_COMPILER_COMMON_HH_
#define KIVI_SRC_BACKEND_COMPILER_COMMON_HH_

#include <string_view>
#include <variant>
#include <ostream>

namespace compiler
{
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

		/// Label if one is present
		std::optional<std::string_view> label;
		std::optional<bool> is_fun;

		/// The expected number of operands
		int operands;
		instruction(const std::string_view& t_name,
			int t_operands = 0,
			const std::optional<std::string_view> t_label = {},
			std::optional<bool> t_is_fun = { false })
			: name{ t_name }, operands{ t_operands }, label{ t_label }, is_fun{ t_is_fun }
		{
		}

		void put_label(const std::string_view& t_label, bool t_is_fun)
		{
			label.emplace(t_label);
			is_fun.emplace(t_is_fun);
		}

		bool operator==(const instruction& rhs) const
		{
			return name == rhs.name && operands == rhs.operands;
		}

		friend std::ostream& operator<<(std::ostream& os, const instruction& instruction)
		{
			os << "{ name: " << instruction.name << ", operands: " << instruction.operands << "}";
			return os;
		}
	};
}

#endif //KIVI_SRC_BACKEND_COMPILER_COMMON_HH_

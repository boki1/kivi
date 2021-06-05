#ifndef KIVI_SRC_BACKEND_COMPILER_COMMON_HH_
#define KIVI_SRC_BACKEND_COMPILER_COMMON_HH_

#include <string_view>
#include <variant>

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
		// TODO: word<T>
		using operand_type = std::vector<std::variant<rregister, word<uint32_t>>>;

		std::string_view name;
		int bytes;
		int opcode;
		instruction::operand_type operands{};
		instruction(const std::string_view& t_name, int t_bytes, int t_opcode, instruction::operand_type t_operand = {})
			: name{ t_name }, bytes{ t_bytes }, opcode{ t_opcode }, operands{ move(t_operand) }
		{
		}
	};
}

#endif //KIVI_SRC_BACKEND_COMPILER_COMMON_HH_

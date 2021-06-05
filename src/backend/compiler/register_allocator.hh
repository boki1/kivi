#ifndef KIVI_REGISTER_ALLOCATOR_HH
#define KIVI_REGISTER_ALLOCATOR_HH

#include <optional_ref/optional_ref.hh>

#include "interference_graph.hh"

namespace compiler
{
	class register_allocator
	{
	 private:
		std::optional<compiler::interference_graph> m_graph{};

		// std::optional<std::vector<...>> m_excess;

		/// The input of the register allocator
		/// @note It is _required_ to first be passed through the instruction selection process before performing register renaming.
		/// Thus, this the value is optional.
		/// @note This `optional_ref` implementation is taken from `https://github.com/hpesoj/gsl-pointers/`.
		gsl::optional_ref<const std::vector<instruction>> m_input{};

		/// The output of the register allocator process
		std::vector<instruction> m_output{};

	 public:
		register_allocator() = default;

		explicit register_allocator(const std::vector<instruction>& t_input)
			: m_input{ t_input }
		{
		}

	 public:
		bool operator()()
		{
			return false;
		}

		bool build_interference_graph()
		{
			return false;
		}

		bool spill_excess()
		{
			return false;
		}

		[[nodiscard]] const std::vector<instruction>&
		fetch_output()
		{
			return m_output;
		}
	};
}

#endif //KIVI_REGISTER_ALLOCATOR_HH

#ifndef KIVI_EMITTER_HH
#define KIVI_EMITTER_HH

#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>

#include "machine_target.hh"

using mt = compiler::machine_target;
using std::move;

namespace compiler
{

	class emitter
	{

	 private:
		/// Resulting output file which contains the assembly of the program
		std::string m_output_file;

		/// Result assembly
		std::stringstream m_sstr{};

		/// Concrete machine architecture
		machine_target m_strategy;

		/// Program
		std::vector<instruction> m_program{};

		/// Additional info for debugging during development
		struct meta
		{
			std::unordered_map<ir::tac::vregister_type, std::string_view> functions;
			std::vector<instruction> after_instruction_selection;
		} debug_meta;

		/// Input program in IR form
		const std::vector<ir::tac>& m_three_address_code;

	 public:
		explicit emitter(machine_target&& target, const std::vector<ir::tac>& t_tacs, std::string output_file = "a.asm")
			: m_strategy{ move(target) }, m_output_file{ std::move(output_file) }, m_three_address_code{ t_tacs }, debug_meta{}
		{
		}

	 public:

		/**
		 * @brief Performs the whole compilation phase unless one of the stages fails
		 * @return bool -- True on success and false on error; Fetch the output by calling `fetch_result`
		 */
		bool compile()
		{
			return (select_instructions() && allocate_registers() && prepare_runtime());
		}

		const std::stringstream& fetch_result()
		{
			return m_sstr;
		}

		std::unique_ptr<std::ofstream> commit_and_fetch_result()
		{
			auto fstr = std::make_unique<std::ofstream>(m_output_file);
			if (fstr) *fstr << m_sstr.rdbuf();
			return fstr;
		}

		//!
		//! Single compilation steps
		//!

		/**
		 * @brief Performs instruction selection algorithm on the given program
		 * @note Ran _first_
		 * @return true Successfull execution
		 * @return false Failed
		 */
		bool select_instructions()
		{
			m_strategy.selector_mut().select_for(m_three_address_code);
			const auto[program, functions] = m_strategy.selector().fetch_selected_output();

			debug_meta.after_instruction_selection = program;
			debug_meta.functions = functions;

			return true;
		}

		/**
		 * @brief Performs register allocation algorithm on the given program
		 * @note Ran _after_ `select_instructions()`
		 * @return true
		 * @return false
		 */
		bool allocate_registers()
		{
			return false;
		}

		/// TODO:
		bool prepare_runtime()
		{
			return false;
		}

	 public:
		const std::string& output_file() const
		{
			return m_output_file;
		}
		const std::stringstream& sstr() const
		{
			return m_sstr;
		}
		const machine_target& strategy() const
		{
			return m_strategy;
		}
		const std::vector<instruction>& program() const
		{
			return m_program;
		}
		const std::vector<ir::tac>& three_address_code() const
		{
			return m_three_address_code;
		}
		const auto& debug() const
		{
			return debug_meta;
		}
	};

} // namespace compiler

#endif // KIVI_EMITTER_HH

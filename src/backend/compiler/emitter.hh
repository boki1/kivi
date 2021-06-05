#ifndef KIVI_EMITTER_HH
#define KIVI_EMITTER_HH

#include <string>
#include <utility>
#include <vector>

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

		/// Input program in three address code form


		/// Concrete machine architecture
		machine_target m_strategy;

		/// Program
		std::vector<instruction> m_program{};

		/// Input program in IR form
		const std::vector<ir::tac>& m_three_address_code;

	 public:
		explicit emitter(machine_target&& target, const std::vector<ir::tac>& t_tacs, std::string output_file = "a.asm")
			: m_strategy{ move(target) }, m_output_file{ std::move(output_file) }, m_three_address_code{ t_tacs }
		{
		}

	 public:

		/// Initiates the whole compilation process
		bool operator()()
		{
			return false;
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
			return false;
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
	};

} // namespace compiler

#endif // KIVI_EMITTER_HH
